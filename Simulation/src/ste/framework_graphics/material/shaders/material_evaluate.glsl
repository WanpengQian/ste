
#include "material.glsl"
#include "material_layer_unpack.glsl"

#include "subsurface_scattering.glsl"

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
	float dotLH = max(dot(l, h), .0f);
	float dotNL = max(dot(n, l), .0f);

	// Tints
	vec3 specular_tint = vec3(1);
	vec3 sheen_tint = vec3(1);

	// Specular color
	vec3 c_spec = mix(specular_tint, base_color, descriptor.metallic);

	// Specular
	vec3 Specular;
	if (descriptor.anisotropy_ratio != 1.f) {
		float rx = descriptor.roughness * descriptor.anisotropy_ratio;
		float ry = descriptor.roughness / descriptor.anisotropy_ratio;

		Specular = cook_torrance_ansi_brdf(n, t, b,
										   v, l, h,
										   rx, ry,
										   F0, c_spec,
										   D, G, F);
	} else {
		Specular = cook_torrance_iso_brdf(n, 
										  v, l, h,
										  descriptor.roughness,
										  F0, c_spec,
										  D, G, F);
	}

	// Diffuse
	vec3 Diffuse = diffuse_color * disney_diffuse_brdf(n, v, l, h,
													   descriptor.roughness);

	// Evaluate BRDF
	vec3 brdf = Specular + (1.f - descriptor.metallic) * Diffuse;
	return brdf * irradiance * dotNL;
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

	vec3 x = n * sqrt(cosine2);
	v = x - ior * cross(n, -t);

	return true;
}

float material_attenuation_through_layer(vec3 v, vec3 l, 
										 float F0, float metallic,
										 float F, float G,
										 out vec3 h) {
	h = normalize(v + l);
	float dotLH = max(dot(l, h), .0f);

	float F21 = fresnel_schlick(F0, dotLH);
	
	float T12 = 1.f - F;
	float T21 = 1.f - F21;
	float g = (1.f - G) + T21 * G;
	float passthrough = 1.f - metallic;

	return max(.0f, T12 * g * passthrough);
}

vec3 material_evaluate_radiance(material_layer_descriptor layer,
								vec3 position,
								vec3 n,
								vec3 t,
								vec3 b,
								vec3 v,
								vec3 l,
								float object_thickness,
								light_descriptor ld,
								sampler2DArray microfacet_refraction_ratio_fit_lut,
								samplerCubeArray shadow_maps, uint light,
								float light_dist,
								float occlusion,
								float external_medium_ior = 1.00029f) {
	float D;
	float G;
	float F;
	vec3 rgb = vec3(0);
	
	material_layer_unpacked_descriptor descriptor = material_layer_unpack(layer);
	
	vec3 attenuation_coefficient = descriptor.attenuation_coefficient;
	bool has_subsurface_scattering = all(greaterThan(attenuation_coefficient, vec3(.0)));

	// Early bail
	if (occlusion <= .0f && !has_subsurface_scattering)
		return vec3(.0f);
		
	vec3 irradiance = light_irradiance(ld, light_dist) * occlusion;

	float F0 = material_convert_ior_to_F0(external_medium_ior, layer.ior);
	vec3 base_color = descriptor.color.rgb;

	vec3 atten = vec3(1.f);
	vec3 h = normalize(v + l);
	
	vec3 outer_back_layers_attenuation_approximation_for_sss = vec3(1.f);

	while (layer.next_layer_id != material_none) {
		material_layer_descriptor next_layer = mat_layer_descriptor[layer.next_layer_id];

		float thickness_scale = 1.f;

		float thickness = thickness_scale * descriptor.thickness;
		float metallic = descriptor.metallic;
		float roughness = descriptor.roughness;

		vec3 in_v = v;
		vec3 in_l = l;
		
		//bool total_internal_reflection = !material_snell_refraction(v, n, layer.ior, next_layer.ior) || !material_snell_refraction(l, n, layer.ior, next_layer.ior);
		//if (total_internal_reflection) {
			v = in_v;
			l = in_l;
		//}

		float refracted_light = 1.f;
		if (layer.ior > next_layer.ior) {
			refracted_light = ggx_refraction_ratio(microfacet_refraction_ratio_fit_lut, 
												   v, n, 
												   roughness, 
												   layer.ior, next_layer.ior);
		}
	
		float dotNV = max(epsilon, dot(n,v));
		float dotNL = max(epsilon, dot(n,l));
		float path_length = thickness * (1.f / dotNV + 1.f / dotNL);

		vec3 extinction = vec3(1.f) - exp(-path_length * attenuation_coefficient);
		vec3 scattering = refracted_light * extinction * base_color;

		rgb += atten * material_evaluate_layer_radiance(descriptor,
														n, t, b,
														in_v, in_l, h,
														F0,
														irradiance,
														base_color,
														scattering,
														D, G, F);
	
		float layer_surface_attenuation = material_attenuation_through_layer(v, l,
																			 F0, metallic,
																			 F, G,
																			 h);

		outer_back_layers_attenuation_approximation_for_sss *= exp(-thickness * attenuation_coefficient) * vec3((1.f - F0) * (1.f - metallic));
		atten *= (vec3(1.f) - extinction) * refracted_light * layer_surface_attenuation;

		F0 = material_convert_ior_to_F0(layer.ior, next_layer.ior);
		layer = next_layer;
		descriptor = material_layer_unpack(next_layer);
		
		attenuation_coefficient = descriptor.attenuation_coefficient;
		base_color = descriptor.color.rgb;
	}
	
	has_subsurface_scattering = has_subsurface_scattering && all(greaterThan(attenuation_coefficient, vec3(.0)));
			
	vec3 extinction = has_subsurface_scattering ? 
							vec3(1.f) - exp(-object_thickness * attenuation_coefficient) :
							vec3(1.f);
	vec3 scattering = extinction * base_color;

	rgb += atten * material_evaluate_layer_radiance(descriptor,
													n, t, b,
													v, l, h,
													F0,
													irradiance,
													base_color,
													scattering,
													D, G, F);

	atten *= material_attenuation_through_layer(v, l,
												F0, descriptor.metallic,
												F, G,
												h);

	bool fully_attenuated = all(lessThan(atten, vec3(.0001f)));
	if (has_subsurface_scattering && !fully_attenuated) {
		outer_back_layers_attenuation_approximation_for_sss *= (1.f - F0) * (1.f - descriptor.metallic);
		rgb += atten * subsurface_scattering(descriptor, 
											 base_color,
											 position,
											 n,
											 outer_back_layers_attenuation_approximation_for_sss,
							 				 object_thickness,
											 ld,
											 shadow_maps, light,
											 -v) * 100;
	}

	return rgb;
}
