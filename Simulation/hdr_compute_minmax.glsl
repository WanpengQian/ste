
#type compute
#version 450

#include "hdr_common.glsl"

layout(local_size_x = 32, local_size_y = 32) in;

layout(binding = 0) uniform sampler2D hdr;

layout(r32f, binding = 0) uniform image2D hdr_lums;
layout(std430, binding = 2) coherent buffer hdr_bokeh_parameters_buffer {
	hdr_bokeh_parameters params;
};
layout(std430, binding = 3) readonly buffer hdr_bokeh_parameters_prev_buffer {
	hdr_bokeh_parameters prev_params;
};

uniform float time;

void main() {
	vec2 ts = textureSize(hdr, 0);
	vec4 lums0 = textureGather(hdr, vec2(gl_GlobalInvocationID.xy) * 4 / ts , 2);
	vec4 lums1 = textureGather(hdr, (vec2(gl_GlobalInvocationID.xy) * 4 + vec2(2,0)) / ts, 2);
	vec4 lums2 = textureGather(hdr, (vec2(gl_GlobalInvocationID.xy) * 4 + vec2(2,2)) / ts, 2);
	vec4 lums3 = textureGather(hdr, (vec2(gl_GlobalInvocationID.xy) * 4 + vec2(0,2)) / ts, 2);
	vec4 ls = vec4(dot(lums0, vec4(.25f)),
				   dot(lums1, vec4(.25f)),
				   dot(lums2, vec4(.25f)),
				   dot(lums3, vec4(.25f)));
	float l = hdr_lum(dot(ls, vec4(.25f)));
	
	if (l >= min_luminance) {
		int int_l = floatBitsToInt(l);
	
		imageStore(hdr_lums, ivec2(gl_GlobalInvocationID.xy), vec4(l,0,0,0));
	
		atomicMin(params.lum_min, int_l);
		atomicMax(params.lum_max, int_l);
	}

	barrier();
	memoryBarrierShared();

	if (gl_GlobalInvocationID.xy == ivec2(0,0)) {
		float t = clamp(.25f * time, 0, 1);
		params.lum_min = floatBitsToInt(t * intBitsToFloat(params.lum_min) + (1 - t) * intBitsToFloat(prev_params.lum_min));
		params.lum_max = floatBitsToInt(t * intBitsToFloat(params.lum_max) + (1 - t) * intBitsToFloat(prev_params.lum_max));
	}
}
