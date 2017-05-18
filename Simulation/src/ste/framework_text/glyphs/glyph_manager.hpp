// StE
// © Shlomi Steinberg, 2015-2016

#pragma once

#include <glyph.hpp>
#include <ste_context.hpp>
#include <glyph_factory.hpp>
#include <font.hpp>
#include <format.hpp>

#include <command_recorder.hpp>

#include <surface_factory.hpp>
#include <device_buffer.hpp>
#include <device_image.hpp>
#include <stable_vector.hpp>
#include <sampler.hpp>
#include <std430.hpp>

#include <exception>

#include <optional.hpp>
#include <lib/unique_ptr.hpp>
#include <lib/string.hpp>
#include <lib/vector.hpp>
#include <lib/unordered_map.hpp>
#include <utility>
#include <lib/concurrent_queue.hpp>

namespace ste {
namespace text {

/**
 *	@brief	Handles glyph storage, loading and generating the glyph buffer and glyph textures.
 */
class glyph_manager {
private:
	struct buffer_glyph_descriptor : gl::std430<std::uint32_t, std::uint32_t, std::int32_t, std::int32_t, std::uint32_t> {
		const glyph::glyph_metrics& metrics() const {
			glyph::glyph_metrics m;
			m.width = get<0>();
			m.height = get<1>();
			m.start_y = get<2>();
			m.start_x = get<3>();

			return m;
		}
		const auto& glyph_index() const { return get<4>(); }

		buffer_glyph_descriptor() = default;
		buffer_glyph_descriptor(const glyph::glyph_metrics& metrics,
								std::uint32_t glyph_index) {
			get<0>() = metrics.width;
			get<1>() = metrics.height;
			get<2>() = metrics.start_y;
			get<3>() = metrics.start_x;

			get<4>() = glyph_index;
		}
	};

public:
	struct glyph_descriptor {
		glyph::glyph_metrics metrics;
		int advance_x;
		int buffer_index;
	};

	using glyph_texture = gl::texture<gl::image_type::image_2d>;

	struct font_storage {
		using glyphs_t = lib::unordered_map<wchar_t, optional<glyph_descriptor>>;
		glyphs_t glyphs;
	};

	struct loaded_glyphs_queue_item {
		font_storage::glyphs_t::iterator glyphit;
		glyph_texture texture;
		glyph_descriptor descriptor;

		loaded_glyphs_queue_item() = default;
	};
	
	using loaded_glyphs_queue_t = lib::concurrent_queue<loaded_glyphs_queue_item>;

private:
	std::reference_wrapper<const ste_context> context;
	glyph_factory factory;

	lib::unordered_map<font, font_storage> fonts;

	lib::vector<buffer_glyph_descriptor> pending_glyphs;

	gl::stable_vector<buffer_glyph_descriptor> buffer;
	lib::vector<glyph_texture> glyph_textures;
	gl::sampler text_glyph_sampler;

	loaded_glyphs_queue_t loaded_glyphs_queue;

private:
	/**
	 *	@brief	Thread-safe glyph loader. Loaded glyph will be inserted into pending queue 'loaded_glyphs_queue'.
	 */
	void glyph_loader(const font &font, wchar_t codepoint, font_storage::glyphs_t::iterator &&glyphit) {
		// Cache key
		lib::string cache_key = lib::string("ttfdf") + font.get_path().string() + lib::to_string(static_cast<std::uint32_t>(codepoint));

		// Check cache
		optional<glyph> og;
		try {
			og = context.get().engine().cache().get<glyph>(cache_key);
		}
		catch (const std::exception &) {
			og = none;
		}

		if (!og) {
			// If can't load from cache, rasterize glyph from factory
			glyph g = factory.create_glyph(font, codepoint);
			if (g.empty())
				return;

			// And store in cache
			glyph copy_g = g;
			context.get().engine().cache().insert<glyph>(cache_key, std::move(copy_g));

			og = std::move(g);
		}

		if (og.get().glyph_distance_field == nullptr) {
			// Font doesn't have glyph for requested codepoint
			assert(false);
			return;
		}

		// Create image and view
		auto image = resource::surface_factory::image_from_surface_2d<gl::format::r32_sfloat>(context.get(),
																							  std::move(*og.get().glyph_distance_field),
																							  gl::image_usage::sampled,
																							  gl::image_layout::shader_read_only_optimal,
																							  false);

		// Store all data in pending queue
		glyph_texture texture(std::move(image));
		glyph_descriptor gd;
		gd.metrics = og.get().metrics;

		loaded_glyphs_queue_item item = { std::move(glyphit), std::move(texture), std::move(gd) };

		loaded_glyphs_queue.push(std::move(item));
	}

	/**
	*	@brief	Pops the pending glyphs queue generated by async loading, and inserts them into pending glyph buffer. 
	*/
	void empty_loaded_descriptors_queue() {
		loaded_glyphs_queue_t::stored_ptr ptr(nullptr);
		while((ptr = loaded_glyphs_queue.pop()) != nullptr) {
			auto index = static_cast<std::uint32_t>(glyph_textures.size());
			glyph_textures.push_back(std::move(ptr->texture));

			glyph_descriptor& gd = ptr->descriptor;
			gd.buffer_index = index;

			buffer_glyph_descriptor bgd(gd.metrics, index);

			pending_glyphs.push_back(bgd);
			ptr->glyphit->second = std::move(gd);
		}
	}

public:
	glyph_manager(const ste_context &context)
		: context(context), 
		buffer(context, gl::buffer_usage::storage_buffer),
		text_glyph_sampler(context.device(),
						   gl::sampler_parameter::filtering(gl::sampler_filter::linear, 
															gl::sampler_filter::linear),
						   gl::sampler_parameter::address_mode(gl::sampler_address_mode::clamp_to_border, 
															   gl::sampler_address_mode::clamp_to_border),
						   gl::sampler_parameter::anisotropy(16.f))
	{}

	/**
	*	@brief	Returns the glyph descriptor for a specific font and codepoint. If not available, will load asynchronously and return none.
	*/
	optional<const glyph_descriptor*> glyph_for_font(const font &font, wchar_t codepoint) {
		if (!loaded_glyphs_queue.is_empty_hint())
			empty_loaded_descriptors_queue();

		// Find , or create if none, glyph storage for requested font
		auto it = this->fonts.find(font);
		if (it == this->fonts.end())
			it = this->fonts.emplace_hint(it, std::make_pair(font, font_storage()));

		// Find glyph in storage
		// If not found, enqueue glyph creation and return none.
		auto glyphit = it->second.glyphs.lower_bound(codepoint);
		if (glyphit == it->second.glyphs.end() || glyphit->first != codepoint) {
			// Mark glyph as loading
			glyphit = it->second.glyphs.emplace_hint(glyphit, std::make_pair(codepoint, none));

			context.get().engine().task_scheduler().schedule_now([=, glyphit = std::move(glyphit)]() mutable {
				glyph_loader(font, codepoint, std::move(glyphit));
			});

			return none;
		}

		// Glyph found but not loaded yet?
		if (!glyphit->second)
			return none;

		const auto* ptr = &glyphit->second.get();
		return ptr;
	}

	/**
	*	@brief	Returns spacing between a couple of glyphs.
	*/
	int spacing(const font &font, const std::pair<wchar_t, wchar_t> &chars, int pixel_size) {
		return factory.read_kerning(font, chars, pixel_size);
	}

	/**
	*	@brief	Should be called from a glyph renderer. Records update commands to upload newly loaded glyphs into device glyph buffer.
	*/
	range<std::uint64_t> update_pending_glyphs(gl::command_recorder &recorder) {
		if (!pending_glyphs.size()) {
			// Nothing to update
			return { 0,0 };
		}

		range<std::uint64_t> ret;
		ret.start = buffer.size();
		ret.length = pending_glyphs.size();

		// Update
		recorder << buffer.push_back_cmd(pending_glyphs);
		pending_glyphs.clear();

		return ret;
	}

	/**
	*	@brief	Used to preload glyphs. Enqueues load tasks for all provided codepoints and returns a future to the task.
	*/
	auto enqueue_glyphs_load(const font &font, lib::vector<wchar_t> codepoints) {
		auto it = this->fonts.find(font);
		if (it == this->fonts.end())
			it = this->fonts.emplace_hint(it, std::make_pair(font, font_storage()));

		lib::vector<std::pair<wchar_t, font_storage::glyphs_t::iterator>> glyphs_to_load;
		glyphs_to_load.reserve(codepoints.size());
		for (wchar_t codepoint : codepoints) {
			auto glyphit = it->second.glyphs.find(codepoint);
			if (glyphit == it->second.glyphs.end())
				glyphit = it->second.glyphs.emplace_hint(glyphit);
			else if (glyphit->second)
				continue;

			glyphs_to_load.emplace_back(codepoint, std::move(glyphit));
		}

		return context.get().engine().task_scheduler().schedule_now([=, glyphs_to_load = std::move(glyphs_to_load)]() mutable {
			for (auto &p : glyphs_to_load) {
				this->glyph_loader(font, p.first, std::move(p.second));
			}
		});
	}

	auto &textures() const { return glyph_textures; }
	auto &sampler() const { return text_glyph_sampler; }
	auto &ssbo() const { return buffer; }
};

}
}
