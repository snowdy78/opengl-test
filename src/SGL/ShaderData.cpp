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
		shader = glCreateShader(toShaderType(type));
		auto sc = source_code.c_str();
		glShaderSource(shader, 1, &sc, nullptr);
	}

	GLenum ShaderData::toShaderType(Type type) 
	{
		if (type == Vertex)
			return GL_VERTEX_SHADER;
		if (type == Fragment)
			return GL_FRAGMENT_SHADER;
		if (type == Geometry)
			return GL_GEOMETRY_SHADER;
		if (type == TessEvaluation)
			return GL_TESS_EVALUATION_SHADER;
		if (type == TessControl)
			return GL_TESS_CONTROL_SHADER;
		if (type == Compute)
			return GL_COMPUTE_SHADER;
		return -1;
	}

	GLenum ShaderData::toBufferAllocationType(BufferAllocationType type) 
	{
		if (type == Static)
			return GL_STATIC_DRAW;
		if (type == Dynamic)
			return GL_DYNAMIC_DRAW;
		if (type == Stream)
			return GL_STREAM_DRAW;
		return -1;
	}
} // namespace sgl
