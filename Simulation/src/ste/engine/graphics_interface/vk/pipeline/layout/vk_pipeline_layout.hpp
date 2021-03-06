//	StE
// � Shlomi Steinberg 2015-2016

#pragma once

#include <stdafx.hpp>

#include <vulkan/vulkan.h>
#include <vk_logical_device.hpp>
#include <vk_ext_debug_marker.hpp>
#include <vk_descriptor_set_layout.hpp>
#include <vk_push_constant_layout.hpp>

#include <vk_host_allocator.hpp>
#include <optional.hpp>

#include <lib/vector.hpp>
#include <allow_type_decay.hpp>
#include <alias.hpp>

namespace ste {
namespace gl {

namespace vk {

template <typename host_allocator = vk_host_allocator<>>
class vk_pipeline_layout : public allow_type_decay<vk_pipeline_layout<host_allocator>, VkPipelineLayout> {
private:
	optional<VkPipelineLayout> layout;
	alias<const vk_logical_device<host_allocator>> device;

public:
	vk_pipeline_layout(const vk_logical_device<host_allocator> &device,
					   const lib::vector<const vk_descriptor_set_layout<host_allocator>*> &set_layouts,
					   const char *name,
					   const lib::vector<vk_push_constant_layout> &push_constant_layouts = {}) : device(device) {
		lib::vector<VkPushConstantRange> push_constant_layout_descriptors;
		push_constant_layout_descriptors.reserve(push_constant_layouts.size());
		for (auto &p : push_constant_layouts)
			push_constant_layout_descriptors.push_back(p);

		lib::vector<VkDescriptorSetLayout> layouts;
		layouts.reserve(set_layouts.size());
		for (auto &s : set_layouts)
			layouts.push_back(*s);

		VkPipelineLayoutCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		create_info.pNext = nullptr;
		create_info.flags = 0;
		create_info.pushConstantRangeCount = static_cast<std::uint32_t>(push_constant_layout_descriptors.size());
		create_info.pPushConstantRanges = push_constant_layout_descriptors.data();
		create_info.setLayoutCount = static_cast<std::uint32_t>(layouts.size());
		create_info.pSetLayouts = layouts.data();

		VkPipelineLayout pipeline_layout;
		const vk_result res = vkCreatePipelineLayout(device, &create_info, &host_allocator::allocation_callbacks(), &pipeline_layout);
		if (!res) {
			throw vk_exception(res);
		}

		// Set object debug marker
		vk_debug_marker_set_object_name(device,
										pipeline_layout,
										VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_LAYOUT_EXT,
										name);

		this->layout = pipeline_layout;
	}
	~vk_pipeline_layout() noexcept {
		destroy_pipeline_layout();
	}

	vk_pipeline_layout(vk_pipeline_layout &&) = default;
	vk_pipeline_layout &operator=(vk_pipeline_layout &&o) noexcept {
		destroy_pipeline_layout();

		layout = std::move(o.layout);
		device = std::move(o.device);

		return *this;
	}
	vk_pipeline_layout(const vk_pipeline_layout &) = delete;
	vk_pipeline_layout &operator=(const vk_pipeline_layout &) = delete;

	void destroy_pipeline_layout() {
		if (layout) {
			vkDestroyPipelineLayout(device.get(), *this, &host_allocator::allocation_callbacks());
			layout = none;
		}
	}

	auto& get() const { return layout.get(); }
};

}

}
}
