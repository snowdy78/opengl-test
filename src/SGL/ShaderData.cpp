#include "SGL/ShaderData.hpp"
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iostream>


namespace sgl
{
	ShaderData::ShaderData() {}

	ShaderData::ShaderData(Type type, const std::string &shader_code)
		: type(type)
	{
		create(shader_code);
	}

	ShaderData::~ShaderData()
	{
	}

	GLuint &ShaderData::operator*()
	{
		return shader;
	}

	const GLuint &ShaderData::operator*() const
	{
		return shader;
	}

	ShaderData::Type ShaderData::getType() const
	{
		return type;
	}
	bool ShaderData::compile()
	{
		if (!is_created)
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
		if (is_created)
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
		create(source_code);
		return true;
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
	void ShaderData::create(const std::string &source_code) 
	{
		if (is_created)
			glDeleteShader(shader);
		shader = glCreateShader(retype[type]);
		const char *code = source_code.c_str();
		glShaderSource(shader, 1, &code, nullptr);
		is_created = true;
	}
} // namespace sgl
