#include "SGL/ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>

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
			GL_ARRAY_BUFFER, sizeof(glm::mat3), glm::value_ptr(point_mat3),
			buffer_type == Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW
		);
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, sizeof(glm::mat3), glm::value_ptr(color_mat3),
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

	void ShaderProgram::setPoints(const glm::mat3 &mat3)
	
	{
	
		point_mat3 = mat3;
	
	}

	void ShaderProgram::setPalette(const glm::mat3 &mat3)
	
	{
	
		color_mat3 = mat3;
	
	}

} // namespace sgl
