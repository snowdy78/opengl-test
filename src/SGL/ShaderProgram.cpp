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
		Palette palette(vertices.getPalette());
		PointArray point_array(vertices.getPointArray());
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, palette.size() * sizeof(glm::vec3), point_array.ptr(),
			buffer_type == Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW
		);
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, sizeof(glm::mat3), palette.ptr(), buffer_type == Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW
		);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glVertexAttribPointer(0, PointArray::value_type::length(), GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, Palette::value_type::length(), GL_FLOAT, GL_FALSE, 0, nullptr);
		need_render = true;
	}

	void ShaderProgram::attach(ShaderData &shader)
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

	void ShaderProgram::setVertexCount(size_t count)
	{
		vertices.resize(count);
	}

	Vertex &ShaderProgram::getVertex(size_t i)
	{
		return vertices[i];
	}

	const Vertex &ShaderProgram::getVertex(size_t i) const
	{
		return vertices[i];
	}


} // namespace sgl
