// StE
// © Shlomi Steinberg, 2015-2016

#pragma once

#include "stdafx.hpp"

#include "GLSLShader.hpp"
#include "GLSLProgram.hpp"

#include <memory>

#include <string>
#include <list>
#include <map>

#include "task.hpp"
#include "StEngineControl.hpp"

#include "optional.hpp"

#define BOOST_FILESYSTEM_NO_DEPRECATED 
#include <boost/filesystem.hpp>

namespace StE {
namespace Resource {

class GLSLProgramFactory {
private:
	static const std::unordered_map<std::string, Core::GLSLShaderType> type_map;

private:
	~GLSLProgramFactory() {}
	
	static optional<boost::filesystem::path> resolve_program(const std::string &program_name);

	static std::string load_source(const boost::filesystem::path &path);

	static std::unique_ptr<Core::GLSLShaderGeneric> compile_from_path(const boost::filesystem::path &path);
	static std::unique_ptr<Core::GLSLShaderGeneric> compile_from_source(const boost::filesystem::path &path, std::string src, Core::GLSLShaderProperties prop, Core::GLSLShaderType);

	static std::vector<std::string> find_includes(const boost::filesystem::path &path);
	static bool parse_include(const boost::filesystem::path &, int, std::string &, std::vector<std::string> &);
	static bool parse_parameters(std::string &, Core::GLSLShaderProperties &, Core::GLSLShaderType &);
	static std::string parse_directive(const std::string &, const std::string &, std::string::size_type &, std::string::size_type &);

public:
	static task<std::unique_ptr<Core::GLSLProgram>> load_program_task(const StEngineControl &context, const std::vector<std::string> &names);
};

}
}
