//	StE
// � Shlomi Steinberg 2015-2017

#pragma once

#include <stdafx.hpp>
#include <vulkan/vulkan.h>
#include <vk_handle.hpp>
#include <vk_ext_debug_marker.hpp>

#include <vk_pipeline.hpp>
#include <vk_logical_device.hpp>
#include <vk_shader.hpp>
#include <vk_host_allocator.hpp>
#include <vk_shader_stage_descriptor.hpp>

#include <vk_pipeline_layout.hpp>
#include <vk_pipeline_cache.hpp>

namespace ste {
namespace gl {

namespace vk {

template <typename host_allocator = vk_host_allocator<>>
class vk_pipeline_compute : public vk_pipeline<host_allocator> {
public:
	vk_pipeline_compute(const vk_logical_device<host_allocator> &device,
						const vk_shader_stage_descriptor<host_allocator> &shader_stage_descriptor,
						const vk_pipeline_layout<host_allocator> &layout,
						const char *name,
						const vk_pipeline_cache<host_allocator> *cache = nullptr) : vk_pipeline(device) {
		assert(shader_stage_descriptor.stage == VK_SHADER_STAGE_COMPUTE_BIT && "shader_stage_descriptor must be a compute shader");

		typename vk_shader<host_allocator>::shader_stage_info_t stage_info;
		shader_stage_descriptor.shader->shader_stage_create_info(VK_SHADER_STAGE_COMPUTE_BIT,
																 stage_info,
																 *shader_stage_descriptor.specializations);

		VkComputePipelineCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		create_info.pNext = nullptr;
		create_info.flags = 0;
		create_info.stage = stage_info.stage_info;
		create_info.layout = layout;
		create_info.basePipelineHandle = vk_null_handle;
		create_info.basePipelineIndex = 0;

		VkPipeline pipeline;
		const vk_result res = vkCreateComputePipelines(device,
													   cache != nullptr ? static_cast<VkPipelineCache>(*cache) : vk_null_handle,
													   1,
													   &create_info,
													   &host_allocator::allocation_callbacks(),
													   &pipeline);
		if (!res) {
			throw vk_exception(res);
		}

		// Set object debug marker
		vk_debug_marker_set_object_name(device,
										pipeline,
										VK_DEBUG_REPORT_OBJECT_TYPE_PIPELINE_EXT,
										name);

		this->pipeline = pipeline;
	}
	~vk_pipeline_compute() noexcept {}

	vk_pipeline_compute(vk_pipeline_compute &&) = default;
	vk_pipeline_compute &operator=(vk_pipeline_compute &&) = default;
	vk_pipeline_compute(const vk_pipeline_compute &) = delete;
	vk_pipeline_compute &operator=(const vk_pipeline_compute &) = delete;
};

}

}
}
