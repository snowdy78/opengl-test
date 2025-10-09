#include "SGL/ShaderData.hpp"
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iostream>


namespace sgl
{
	ShaderData::ShaderData(Type type)
		: type(type)
	{}
	ShaderData::~ShaderData() {}
	ShaderData::Type ShaderData::getType() const
	{
		return type;
	}
	GLuint ShaderData::getDescriptor() const
	{
		return shader;
	}
	bool ShaderData::compile() const
	{
		if (!exist())
			throw std::runtime_error("Shader is not created");
		glCompileShader(shader);

		GLint compile_status = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
		if (compile_status == GL_FALSE)
		{
			size_t size = 1024;
			GLchar infoLog[size];
			glGetShaderInfoLog(shader, size, nullptr, infoLog);
			std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	void ShaderData::remove()
	{
		if (exist())
			glDeleteShader(shader);
	}
	bool ShaderData::setCode(const std::string &code)
	{
		if (code.empty())
		{
			return false;
		}
		create(code);
		return true;
	}
	ShaderData::ShaderData(ShaderData &&other)
	{
		shader		 = other.shader;
		other.shader = 0;
		type		 = other.type;
		other.type	 = Unknown;
		buffer_type	 = other.buffer_type;
	}
	bool ShaderData::exist() const
	{
		return shader != 0;
	}
	ShaderData::BufferAllocationType ShaderData::getBufferAllocType() const
	{
		return buffer_type;
	}
	void ShaderData::setBufferAllocType(BufferAllocationType type)
	{
		buffer_type = type;
	}
	void ShaderData::create(const std::string &source_code)
	{
		if (type == Unknown)
			throw std::runtime_error("Unknown shader type");
		if (shader != 0)
			glDeleteShader(shader);
		shader	= glCreateShader(type);
		auto sc = source_code.c_str();
		glShaderSource(shader, 1, &sc, nullptr);
	}

	std::string getFileData(const std::string &path, std::ios_base::openmode openmode)
	{
		auto file = std::ifstream(path, openmode);
		if (!file.is_open())
		{
			throw std::runtime_error("File not found '" + path + "'");
		}
		std::string source_code;
		std::string line;
		while (getline(file, line))
		{
			source_code += line + "\n";
		}
		file.close();
		return source_code;
	}
} // namespace sgl
