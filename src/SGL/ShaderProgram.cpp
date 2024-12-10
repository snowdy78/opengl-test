#include "SGL/ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "SGL/ShaderData.hpp"
#include "SGL/Vertex.hpp"

namespace sgl
{
	ShaderProgram::ShaderProgram() {}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program);
	}

	void ShaderProgram::bindBuffers()
	{
		for (auto &shader: shaders)
		{
			size_t i = 0;
			std::vector<GLuint> vbo(shader->layouts.size(), 0);
			for (auto &layout: shader->layouts)
			{
				if (layout.empty())
					continue;

				glGenBuffers(1, &vbo[i]);
				glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
				glBufferData(
					GL_ARRAY_BUFFER, layout[0]->getSizeInBytes(), layout.ptr(),
					layout.getBufferType()
				);

				i++;
				need_render = true;
			}
			GLuint vao = 0;
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
			i = 0;
			for (auto &layout: shader->layouts)
			{
				glEnableVertexAttribArray(i);
				glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
				glVertexAttribPointer(i, layout.size(), GL_DOUBLE, GL_FALSE, 0, nullptr);
			}
		}
	}

	void ShaderProgram::attach(ShaderData &shader)
	{
		shaders.push_back(&shader);
		glAttachShader(program, shader.getGLId());
	}

	void ShaderProgram::render()
	{
		if (need_render)
		{
			glUseProgram(program);
			need_render = false;
		}
	}

	void ShaderProgram::link()
	{
		glLinkProgram(program);
	}

	void ShaderProgram::detach(ShaderData &shader)
	{
		glDetachShader(program, shader.getGLId());
	}
	size_t ShaderProgram::getShaderCount() const
	{
		return shaders.size();
	}
	const Vertex &ShaderProgram::getVertex(size_t i) const
	{
		return vertices[i];
	}
	size_t ShaderProgram::getVertexCount() const
	{
		return vertices.size();
	}
} // namespace sgl
