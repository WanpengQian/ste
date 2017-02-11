
#include "stdafx.hpp"
#include "glsl_program_object.hpp"

#include "log.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <sys/stat.h>

using namespace StE::Core;

bool glsl_program_object::link() {
	if (linked) return true;
	if (!Base::is_valid()) return false;

	for (auto &shader : shaders)
		glAttachShader(get_resource_id(), shader->get_resource_id());
	glLinkProgram(get_resource_id());

	shaders.clear();

	int status = 0;
	glGetProgramiv(get_resource_id(), GL_LINK_STATUS, &status);
	if (!status) {
		// Log and return false
		int length = 0;
		glGetProgramiv(get_resource_id(), GL_INFO_LOG_LENGTH, &length);

		std::string reason;
		if (length > 0) {
			char * c_log = new char[length];
			int written = 0;
			glGetProgramInfoLog(get_resource_id(), length, &written, c_log);
			reason = c_log;
			delete[] c_log;
		}

		ste_log_error() << "Linking GLSL program failed \"" << Text::Attributes::i(this->generate_name()) << "\"! Reason: " << reason;

		return false;
	}
	else {
		linked = true;
		return linked;
	}
}

bool glsl_program_object::link_from_binary(generic_resource::type format, const std::string &data) {
	glProgramBinary(get_resource_id(), format, data.data(), data.length());
	int success = 0;
	glGetProgramiv(get_resource_id(), GL_LINK_STATUS, &success);
	linked = success;
	return success;
}

std::string glsl_program_object::get_binary_representation(generic_resource::type *format) const {
	int bin_len = 0;
	glGetProgramiv(get_resource_id(), GL_PROGRAM_BINARY_LENGTH, &bin_len);
	std::string data;
	data.resize(bin_len);
	glGetProgramBinary(get_resource_id(), bin_len, nullptr, format, &data[0]);

	return data;
}

std::string glsl_program_object::generate_name() const {
	std::string name = "[";
	auto it = shaders.begin();
	while (it != shaders.end()) {
		name += (*it)->get_name();
		++it;
		if (it != shaders.end())
			name += ", ";
	}
	return name + "]";
}
