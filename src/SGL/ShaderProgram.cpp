#include "SGL/ShaderProgram.hpp"
#include <iostream>

namespace sgl
{
	void ShaderProgram::bindBuffers()
	{
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		auto *begin = &color_mat3[0];
		auto *end	= &color_mat3[color_mat3.size()];
		for (auto i = begin; i != end; i++)
		{
			std::cout << *i << std::endl;
		}
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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	void ShaderProgram::attach(Shader &shader)
	{
		glAttachShader(program, *shader);
	}

	void ShaderProgram::render()
	{
		glUseProgram(program);
	}

	void ShaderProgram::link()
	{
		glLinkProgram(program);
	}

} // namespace sgl
