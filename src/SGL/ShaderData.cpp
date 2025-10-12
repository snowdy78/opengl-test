#include "SGL/ShaderData.hpp"
#include <stdexcept>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "SGL/SGLfwd.hpp"
#include "SGL/ShaderProgram.hpp"

namespace sgl
{
	ShaderData::ShaderData(Type type)
		: m_type(type)
	{}
	ShaderData::~ShaderData()
	{
		deleteBuffers();
	}
	ShaderData::Type ShaderData::getType() const
	{
		return m_type;
	}
	bool ShaderData::compile() const
	{
		if (!exist())
			throw std::runtime_error("Shader is not created");
		glCompileShader(m_shader);

		GLint compile_status = 0;
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compile_status);
		if (compile_status == GL_FALSE)
		{
			size_t size = 1024;
			GLchar infoLog[size];
			glGetShaderInfoLog(m_shader, size, nullptr, infoLog);
			std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	void ShaderData::remove()
	{
		if (exist())
			glDeleteShader(m_shader);
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
		m_shader	   = other.m_shader;
		other.m_shader = 0;
		m_type		   = other.m_type;
		other.m_type   = Unknown;
	}
	bool ShaderData::exist() const
	{
		return m_shader != 0;
	}
	void ShaderData::create(const std::string &source_code)
	{
		if (m_type == Unknown)
			throw std::runtime_error("Unknown shader type");
		if (m_shader != 0)
			glDeleteShader(m_shader);
		m_shader = glCreateShader(m_type);
		auto sc	 = source_code.c_str();
		glShaderSource(m_shader, 1, &sc, nullptr);
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
	bool ShaderData::isBuffersGenerated() const
	{
		return !m_descriptors_of_buffers.empty();
	}
	void ShaderData::genBuffers() const
	{
		if (isBuffersGenerated())
			deleteBuffers();
		assignBuffersDescriptors();
		glGenBuffers(m_descriptors_of_buffers.size(), m_descriptors_of_buffers.data());
	}
	void ShaderData::deleteBuffers() const
	{
		glDeleteBuffers(m_descriptors_of_buffers.size(), m_descriptors_of_buffers.data());
		clearBuffersDescriptors();
	}
	size_t ShaderData::getBufferCount() const noexcept
	{
		return m_buffers.size();
	}
	void ShaderData::push(buffer &&buffer, sgl::layout &&layout)
	{
		m_buffers.push_back(std::move(buffer));
		m_layouts.emplace_back(std::move(layout)); // add layout for buffer
	}
	void ShaderData::erase(size_t index)
	{
		m_buffers.erase(m_buffers.begin() + index);
	}
	const buffer &ShaderData::getBuffer(size_t index) const
	{
		return m_buffers[index];
	}
	void ShaderData::bindBuffer(size_t index) const
	{
		glBindBuffer(m_buffers[index].getTargetType(), m_descriptors_of_buffers[index]);
	}
	void ShaderData::bufferData(size_t index) const
	{
		auto &buff = m_buffers[index];
		glBufferData(buff.getTargetType(), buff.length(), buff.data(), buff.getUsageType());
	}
	void ShaderData::enableVertexAttribArray(size_t layout_index) const
	{
		auto &layout = m_layouts[layout_index];
		glEnableVertexAttribArray(layout.location());
	}

	void ShaderData::disableVertexAttribArray(size_t location) const
	{
		glDisableVertexAttribArray(location);
	}
	void ShaderData::attribPointer(size_t layout_index) const
	{
		auto &layout = m_layouts[layout_index];
		glVertexAttribPointer(
			layout.location(), layout.size(), layout.type(), layout.normalized(), layout.stride(), layout.pointer()
		);
	}
	void ShaderData::build() const
	{
		genBuffers();
		for (size_t index = 0; index < m_layouts.size(); index++)
		{
			bindBuffer(index);
			enableVertexAttribArray(index);
			bufferData(index);
			attribPointer(index);
			unbindBuffer(index);
		}
	}
	void ShaderData::attach(const ShaderProgram &shader) const
	{
		glAttachShader(shader.program, m_shader);
	}
	void ShaderData::clear()
	{
		m_buffers.clear();
		m_layouts.clear();
	}
	void ShaderData::assignBuffersDescriptors() const
	{
		m_descriptors_of_buffers.assign(m_buffers.size(), 0);
	}
	void ShaderData::clearBuffersDescriptors() const
	{
		m_descriptors_of_buffers.clear();
	}
	void ShaderData::unbindBuffer(size_t index) const
	{
		glBindBuffer(m_buffers.at(index).getTargetType(), 0);
	}
} // namespace sgl
