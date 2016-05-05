
#type frag
#version 450
#extension GL_NV_gpu_shader5 : require

layout(early_fragment_tests) in;

#include "gbuffer.glsl"
#include "material.glsl"

layout(shared, binding = 6) restrict writeonly buffer gbuffer_data {
	g_buffer_element gbuffer[];
};

layout(binding = 7) uniform atomic_uint gbuffer_ll_counter;
layout(r32ui, binding = 7) restrict uniform uimage2D gbuffer_ll_heads;

#include "gbuffer_store.glsl"

in vec2 frag_texcoords;
in vec3 frag_position;
in vec3 frag_wposition;

layout(binding = 0) uniform sampler2D sky_tex;

uniform float sky_luminance;

void main() {
	vec2 uv = frag_texcoords;
	vec3 P = frag_position;

	vec4 diffuse = vec4(texture(sky_tex, uv).rgb * sky_luminance, 1);

	gbuffer_store(gbuffer_ll_heads, gbuffer_ll_counter, gl_FragCoord.z, uv, f16vec3(0,0,0), f16vec3(0,0,0), material_none, ivec2(gl_FragCoord.xy));
}
