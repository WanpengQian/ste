
#include "stdafx.hpp"
#include "deferred_fbo.hpp"

using namespace StE::Graphics;
using namespace StE::Core;

void deferred_fbo::resize(glm::ivec2 size) {
	if (size.x <= 0 || size.y <= 0)
		return;

	this->size = size;

	depth_output = std::make_unique<Core::RenderTarget>(gli::format::FORMAT_D32_SFLOAT_PACK32, glm::ivec2{ size });
	normal_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_RGB16_SFLOAT_PACK16, glm::ivec2{ size }, 1);
	tangent_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_RGB16_SFLOAT_PACK16, glm::ivec2{ size }, 1);
	position_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_RGB32_SFLOAT_PACK32, glm::ivec2{ size }, 1);
	color_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_RGBA32_SFLOAT_PACK32, glm::ivec2{ size }, 1);
	material_idx_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_R16_SINT_PACK16, glm::ivec2{ size }, 1);
	lin_z_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_R32_SFLOAT_PACK32, glm::ivec2{ size }, 1);
	wposition_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_RGB32_SFLOAT_PACK32, glm::ivec2{ size }, 1);
	wnormal_output = std::make_unique<Core::Texture2D>(gli::format::FORMAT_RGB16_SFLOAT_PACK16, glm::ivec2{ size }, 1);

	fbo.depth_binding_point() = *depth_output;
	fbo[0] = (*position_output)[0];
	fbo[1] = (*color_output)[0];
	fbo[2] = (*normal_output)[0];
	fbo[3] = (*lin_z_output)[0];
	fbo[4] = (*tangent_output)[0];
	fbo[5] = (*material_idx_output)[0];
	fbo[6] = (*wposition_output)[0];
	fbo[7] = (*wnormal_output)[0];
}

void deferred_fbo::bind_output_textures() const {
	0_tex_unit = *normal_output;
	1_tex_unit = *position_output;
	2_tex_unit = *color_output;
	3_tex_unit = *tangent_output;
	4_tex_unit = *material_idx_output;
	5_tex_unit = *wposition_output;
	6_tex_unit = *wnormal_output;
}
