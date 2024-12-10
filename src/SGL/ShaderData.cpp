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

	ShaderData::Type ShaderData::getType() const
	{
		return type;
	}
	bool ShaderData::compile()
	{
		if (!is_created)
			throw std::runtime_error("Shader is not created");
		glCompileShader(id);

		GLint compile_status = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
		if (compile_status == GL_FALSE)
		{
			size_t size = 1024;
			GLchar infoLog[size];
			glGetShaderInfoLog(id, size, nullptr, infoLog);
			std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	void ShaderData::remove()
	{
		if (is_created)
			glDeleteShader(id);
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
			glDeleteShader(id);
		id = glCreateShader(type);
		const char *code = source_code.c_str();
		glShaderSource(id, 1, &code, nullptr);
		is_created = true;
	}
	GLuint ShaderData::getGLId() const
	{
		return id;
	}

	void ShaderData::addLayout(size_t index, ShaderLayout::reference value)
	{
		auto it = layouts.begin();
		std::advance(it, index);
		if (it == layouts.end())
			throw std::out_of_range("Index out of range");
		layouts.insert(it, {&value});
	}
	void ShaderData::setLayoutValue(size_t layout_id, size_t value_id, const void *layout)
	{
		*layouts[layout_id][value_id] = layout;
	}
	const ShaderData::ShaderLayout &ShaderData::layout(size_t index) const
	{
		return layouts[index];
	}
	void ShaderData::removeLayout(size_t index)
	{
		auto it = layouts.begin();
		std::advance(it, index);
		layouts.erase(it);
	}
	size_t ShaderData::getLayoutCount() const
	{
		return layouts.size();
	}
	void ShaderData::insertIntoLayout(size_t index, ShaderLayout::reference layout_value)
	{
		layouts[index].push_back(&layout_value);
	}
	void ShaderData::setLayoutCount(size_t count)
	{
		layouts.resize(count);
	}
} // namespace sgl
