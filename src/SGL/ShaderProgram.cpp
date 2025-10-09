#include "SGL/ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "..\..\include\SGL\SGLfwd.hpp"
namespace sgl
{
	void ShaderProgram::makeBuild() const
	{
		if (size() == 0)
			return;
		for (auto &shader: *this)
			if (!shader.compile())
				return;
		attach();
		link();

		bindBuffers();
		need_build = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program);
		for (auto &buff: vertex_buffers)
		{
			if (buff != 0)
				glDeleteBuffers(1, &buff);
		}
		if (vertex_array != 0)
			glDeleteVertexArrays(1, &vertex_array);
	}

	void ShaderProgram::bindBuffers() const
	{
		std::cout << "build\n";
		auto colors		 = vertices.getPalette().toArray4();
		auto point_array = vertices.getPointArray();
		if (transform.isNeedUpdate())
		{
			transform.update();
		}
		for (auto &point: point_array)
		{
			point = transform.transformPoint(point);
		}
		auto points = point_array.toArray3();
		if (vertex_array != 0)
		{
			glDeleteVertexArrays(1, &vertex_array);
		}
		for (auto &buff: vertex_buffers)
		{
			if (buff != 0)
			{
				glDeleteBuffers(1, &buff);
				buff = 0;
			}
		}
		glGenBuffers(2, vertex_buffers.data());
		glGenVertexArrays(1, &vertex_array);
		glBindVertexArray(vertex_array);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[0]);
		glBufferData(
			GL_ARRAY_BUFFER, sizeof(PointArray::value_type::value_type) * points.size(), points.data(),
			at(0).getBufferAllocType()
		);
		glVertexAttribPointer(0, PointArray::value_type::length(), GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[1]);
		glBufferData(
			GL_ARRAY_BUFFER, sizeof(Palette::value_type::value_type) * colors.size(), colors.data(),
			at(1).getBufferAllocType()
		);
		glVertexAttribPointer(1, Palette::value_type::length(), GL_FLOAT, GL_FALSE, 0, nullptr);
	}
	void ShaderProgram::build() const
	{
		need_build = true;
	}

	void ShaderProgram::attach() const
	{
		for (auto &shader: *this)
		{
			glAttachShader(program, shader.getDescriptor());
		}
	}

	void ShaderProgram::render() const
	{
		if (need_build)
		{
			makeBuild();
		}
		glUseProgram(program);
		glBindVertexArray(vertex_array);
		glDrawArrays(draw_algorithm, 0, vertices.size());
	}

	void ShaderProgram::link() const
	{
		glLinkProgram(program);
	}

	void ShaderProgram::setVertexCount(size_t count)
	{
		vertices.resize(count);
		build();
	}

	size_t ShaderProgram::getVertexCount() const
	{
		return vertices.size();
	}

	ShaderProgram::PrimitiveType ShaderProgram::getPrimitiveType() const
	{
		return draw_algorithm;
	}

	void ShaderProgram::setPrimitiveType(PrimitiveType type)
	{
		draw_algorithm = type;
	}
	const Vertex &ShaderProgram::getVertex(size_t i) const
	{
		return vertices[i];
	}
	void ShaderProgram::setVertex(size_t i, const Vertex &vertex)
	{
		vertices[i] = vertex;
		build();
	}

} // namespace sgl
