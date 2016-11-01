
#include "stdafx.hpp"
#include "shadowmap_projector.hpp"

using namespace StE::Graphics;

void shadowmap_projector::set_context_state() const {
	using namespace Core;

	GL::gl_current_context::get()->enable_depth_test();
	GL::gl_current_context::get()->color_mask(false, false, false, false);
	GL::gl_current_context::get()->enable_state(GL::BasicStateName::CULL_FACE);
//	GL::gl_current_context::get()->cull_face(GL_FRONT);

	auto size = shadow_map->get_cubemaps()->get_size();
	GL::gl_current_context::get()->viewport(0, 0, size.x, size.y);

	scene->get_shadow_projection_buffers().idb.buffer().bind();
	scene->bind_buffers();
	lights->bind_lights_buffer(2);

	4_storage_idx = Core::buffer_object_cast<Core::ShaderStorageBuffer<std::uint32_t>>(lights->get_active_ll_counter());
	5_storage_idx = lights->get_active_ll();

	8_storage_idx = scene->get_shadow_projection_buffers().proj_id_to_light_id_translation_table;

	shadow_gen_program.get().bind();
	shadow_map->get_cube_fbo()->bind();
}

void shadowmap_projector::dispatch() const {
	Core::GL::gl_current_context::get()->clear_framebuffer(false, true);

	Core::GL::gl_current_context::get()->memory_barrier(GL_SHADER_STORAGE_BARRIER_BIT);
	scene->draw_object_group();
}
