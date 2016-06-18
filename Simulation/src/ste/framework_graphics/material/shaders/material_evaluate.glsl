
#include "material.glsl"
#include "material_layer_unpack.glsl"

#include "common.glsl"

vec3 material_evaluate_layer_radiance(material_layer_unpacked_descriptor descriptor,
									  vec3 n,
									  vec3 t,
									  vec3 b,
									  vec3 v,
									  vec3 l,
									  vec3 h,
									  float F0,
									  vec3 irradiance,
									  vec3 base_color,
									  vec3 diffuse_color,
									  out float D,
									  out float G,
									  out float F) {
	// Tints
	vec3 specular_tint = vec3(1);
	vec3 sheen_tint = vec3(1);

	// Specular color
	vec3 c_spec = mix(specular_tint, base_color, descriptor.metallic);

	// Additional sheen color (diffuse at grazing angles)
	vec3 c_sheen = fresnel_schlick_ratio(dot(l,h), descriptor.sheen_power) * sheen_tint * descriptor.sheen;

	// Specular
	vec3 Specular;
	if (descriptor.anisotropy_ratio != 1.f) {
		float roughness_x = descriptor.roughness * descriptor.anisotropy_ratio;
		float roughness_y = descriptor.roughness / descriptor.anisotropy_ratio;

		Specular = cook_torrance_ansi_brdf(n, t, b,
										   v, l, h,
										   roughness_x,
										   roughness_y,
										   F0, c_spec,
										   D, G, F);
	} else {
		Specular = cook_torrance_iso_brdf(n, v, l, h,
										  descriptor.roughness,
										  F0, c_spec,
										  D, G, F);
	}

	// Diffuse
	vec3 Diffuse = diffuse_color * disney_diffuse_brdf(n, v, l, h,
													   descriptor.roughness);

	// Evaluate BRDF
	vec3 brdf = Specular + (1.f - descriptor.metallic) * (Diffuse + c_sheen);
	return brdf * irradiance * dot(n, l);
}

bool material_snell_refraction(inout vec3 v,
							   vec3 n,
							   float ior1,
							   float ior2) {
	vec3 t = cross(n, -v);
	float ior = ior1 / ior2;

	float cosine2 = 1.f - ior * ior * dot(t, t);
	if (cosine2 < .0f)
		return false;

	vec3 normal_by_cosine = n * sqrt(cosine2);
	v = normal_by_cosine - ior * cross(n, -t);

	return true;
}

vec3 material_evaluate_radiance(material_layer_descriptor layer,
								vec3 n,
								vec3 t,
								vec3 b,
								vec3 v,
								vec3 l,
								vec2 uv,
								vec2 duvdx,
								vec2 duvdy,
								vec3 irradiance,
								float external_medium_ior = 1.00029f) {
	float D;
	float G;
	float F;
	vec3 rgb = vec3(0);
	
	material_layer_unpacked_descriptor descriptor = material_layer_unpack(layer, uv, duvdx, duvdy);

	float F0 = material_convert_ior_to_F0(external_medium_ior, layer.ior);
	vec3 base_color = descriptor.base_color.rgb;

	float atten = 1.f;
	vec3 h = normalize(v + l);

	while (layer.next_layer_id != material_none) {
		material_layer_descriptor next_layer = mat_layer_descriptor[layer.next_layer_id];

		float thickness_scale = descriptor.base_color.a;

		float thickness = thickness_scale * descriptor.thickness;
		float metallic = descriptor.metallic;
		float attenuation_coefficient = descriptor.attenuation_coefficient;

		vec3 in_v = v;
		vec3 in_l = l;
		
		bool total_internal_reflection = !material_snell_refraction(v, n, layer.ior, next_layer.ior) || !material_snell_refraction(l, n, layer.ior, next_layer.ior);
		if (total_internal_reflection) {
			v = in_v;
			l = in_l;
			break;
		}
	
		float dotNV = max(epsilon, dot(n,v));
		float dotNL = max(epsilon, dot(n,l));
		float path_length = thickness * (1.f / dotNV + 1.f / dotNL);

		float extinction = 1.f - exp(-path_length * attenuation_coefficient);
		vec3 scattering = extinction * base_color;

		rgb += atten * material_evaluate_layer_radiance(descriptor,
														n, t, b,
														in_v, in_l, h,
														F0,
														irradiance,
														base_color,
														scattering,
														D, G, F);
	
		h = normalize(v + l);
		float F21 = fresnel_schlick(F0, dot(l,h));
	
		float T12 = 1.f - F;
		float T21 = 1.f - F21;
		float g = (1.f - G) + T21 * G;
		float passthrough = 1.f - metallic;

		atten *= max(.0f, (1.f - extinction) * T12 * g * passthrough);
		F0 = material_convert_ior_to_F0(layer.ior, next_layer.ior);

		layer = next_layer;
		descriptor = material_layer_unpack(next_layer, uv, duvdx, duvdy);
		
		base_color = descriptor.base_color.rgb;
	}

	rgb += atten * material_evaluate_layer_radiance(descriptor,
													n, t, b,
													v, l, h,
													F0,
													irradiance,
													base_color,
													base_color,
													D, G, F);

	return rgb;
}
