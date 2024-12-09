#include "SGL/ShaderProgram.hpp"
#include <iostream>

namespace sgl
{
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program);
	}

	void ShaderProgram::bindBuffers()
	{
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, point_mat3.size() * sizeof(GLfloat), &point_mat3[0],
			buffer_type == Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW
		);
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, color_mat3.size() * sizeof(GLfloat), &color_mat3[0],
			buffer_type == Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW
		);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        need_render = true;
	}

	void ShaderProgram::attach(Shader &shader)
	{
		glAttachShader(program, *shader);
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

} // namespace sgl
