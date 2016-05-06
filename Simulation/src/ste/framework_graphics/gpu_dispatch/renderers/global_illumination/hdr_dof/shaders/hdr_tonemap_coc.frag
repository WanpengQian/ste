
#type frag
#version 450
#extension GL_ARB_bindless_texture : require
#extension GL_NV_gpu_shader5 : require

#include "hdr_common.glsl"
#include "gbuffer.glsl"

layout(location = 0) out vec4 rgbout;
layout(location = 1) out vec4 bloomout;
layout(location = 2) out vec2 coc_out;

layout(shared, binding = 0) restrict readonly buffer histogram_sums {
	uint histogram[bins];
};
layout(std430, binding = 2) restrict readonly buffer hdr_bokeh_parameters_buffer {
	hdr_bokeh_parameters params;
};

const float bloom_cutoff = .9f;
const float vision_properties_max_lum = 10.f;

layout(bindless_sampler) uniform sampler2D hdr;
layout(bindless_sampler) uniform sampler1D hdr_vision_properties_texture;
layout(binding = 11) uniform sampler2D depth;

uniform float aperature_radius = .2f;
uniform float f1 = .1f;
uniform float proj22, proj23;

vec2 hdr_zcoc(vec4 RGBL, vec3 XYZ, float acuity, float mesopic) {
	if (XYZ.y > bloom_cutoff) {
		float x = pow((XYZ.y - bloom_cutoff) / (1.f - bloom_cutoff), 8) * (1.f - mesopic);
		bloomout = vec4(RGBL.rgb, x);
	}
	else
		bloomout = vec4(0);

	float focal = params.focus;

	float d = texelFetch(depth, ivec2(gl_FragCoord.xy), 0).x;
	float d_ndc = d * 2.f - 1.f;
	float z_lin = -proj23 / (d_ndc - proj22);

	float s = z_lin;

	float C = aperature_radius * abs(focal - s) / s;
	float c = C * f1 / focal;
	float coc = clamp(smoothstep(0.f, 1.f, c), 0.f, 1.f);
	coc += acuity;

	return vec2(s, clamp(coc, 0.f, 1.f));
}

float hdr_tonemap(float l) {
	float min_lum = intBitsToFloat(params.lum_min);
	float max_lum = intBitsToFloat(params.lum_max);

	float fbin = hdr_bin(max_lum, min_lum, l);
	int bin = int(fbin);
	float frac = fract(fbin);

	float T = float(histogram[bins - 1]);
	float toned_bin_start = bin > 0 ? float(histogram[bin - 1]) / T : .0f;
	float toned_bin_end = float(histogram[bin]) / T;

	float toned_l = mix(toned_bin_start, toned_bin_end, frac);

	return tonemap(toned_l);
}

void main() {
	vec3 hdr_texel = texelFetch(hdr, ivec2(gl_FragCoord.xy), 0).rgb;
	float x = hdr_texel.z;

	float vision_properties_coord = (x - min_luminance) / (vision_properties_max_lum - min_luminance);
	vec4 vision_properties = texture(hdr_vision_properties_texture, vision_properties_coord);
	float scotopic = vision_properties.x;
	float mesopic = vision_properties.y;
	float monochr = vision_properties.z;
	float acuity = vision_properties.w;
	float red_coef = red_response(mesopic);

	float l = hdr_lum(x);
	hdr_texel.z = hdr_tonemap(l) * mix(1.f, .666f, scotopic);

	vec3 XYZ = xyYtoXYZ(hdr_texel);
	vec3 RGB = XYZtoRGB(XYZ);
	RGB.r *= red_coef;
	RGB = mix(RGB, XYZ.yyy, monochr);
	vec4 RGBL = clamp(vec4(RGB, XYZ.y), vec4(0.f), vec4(1.f));

	rgbout = RGBL;
	coc_out = hdr_zcoc(RGBL, XYZ, acuity, mesopic);
}
