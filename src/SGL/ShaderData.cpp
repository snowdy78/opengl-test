#include "SGL/ShaderData.hpp"
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iostream>


namespace sgl
{
	ShaderData::ShaderData() {}

	ShaderData::ShaderData(Type type, const std::string &code_str)
		: type(type)
	{
		create(type, code_str);
	}
	ShaderData::~ShaderData() {}
	ShaderData::Type ShaderData::getType() const
	{
		return type;
	}
	GLuint ShaderData::getDescriptor() const
	{
		return shader;
	}
	bool ShaderData::compile()
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
	bool ShaderData::load(const std::string &path, Type type)
	{
		std::string source_code = loadFromFile(path);
		if (source_code.empty())
		{
			return false;
		}
		this->type = type;
		create(this->type, source_code);
		return true;
	}
	ShaderData::ShaderData(ShaderData &&other) 
	{
	    shader = other.shader;
	    other.shader = 0;
	    type = other.type;
	    other.type = Unknown;
	    buffer_type = other.buffer_type;
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
	std::string ShaderData::loadFromFile(const std::string &path)
	{
		std::ifstream file(path);
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
	void ShaderData::create(Type type, const std::string &source_code) 
	{
		if (type == Unknown) 
			throw std::runtime_error("Unknown shader type");
		if (shader != 0)
			glDeleteShader(shader);
		shader = glCreateShader(type);
		auto sc = source_code.c_str();
		glShaderSource(shader, 1, &sc, nullptr);
	}

} // namespace sgl
