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
		code = (char *) malloc(shader_code.size() + 1);
		code[shader_code.size()] = '\0';
		for (int s = 0; code[s] != '\0'; ++s)
		{
			code[s] = shader_code[s];
		}

		shader = glCreateShader(type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		glShaderSource(shader, 1, &code, nullptr);
	}

	ShaderData::~ShaderData()
	{
		delete[] code;
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
		if (code == nullptr)
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
		if (code != nullptr)
			glDeleteShader(shader);
		delete[] code;
		code = nullptr;
	}
	void ShaderData::load(const std::string &path, Type type)
	{
		bool loaded = code;
		if (!loadFromFile(path))
		{
			throw std::runtime_error("File not found in '" + path + "'");
		}
		this->type = type;
		if (code)
			glDeleteShader(shader);
		shader = glCreateShader(type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
		glShaderSource(shader, 1, &code, nullptr);
	}
	bool ShaderData::loadFromFile(const std::string &path)
	{
		std::ifstream file(path);
		if (!file.is_open())
		{
			return false;
		}
		std::string source_code;
		std::string line;
		while (getline(file, line))
		{
			source_code += line + "\n";
		}
		file.close();
		code = new char[source_code.size() + 1];
		code[source_code.size()] = '\0';
		for (int s = 0; s != source_code.size(); ++s)
		{
			code[s] = source_code[s];
		}
		return true;
	}
} // namespace sgl
