#include "SGL/ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "SGL/SGLdecl.hpp"

namespace sgl
{
	GLenum ShaderProgram::toDrawAlgorithm(PrimitiveType draw_algorithm) 
	{
		switch (draw_algorithm) 
		{
		case TriangleFan:
			return GL_TRIANGLE_FAN;
		case TriangleStrip:
			return GL_TRIANGLE_STRIP;
		case Triangles:
			return GL_TRIANGLES;
		case LineStrip:
			return GL_LINE_STRIP;
		case LineLoop:
			return GL_LINE_LOOP;
		case Lines:
			return GL_LINES;
		case Points:
			return GL_POINTS;
		case Quads:
			return GL_QUADS;
		default:
			return Unknown;
		}
		return Unknown;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program);
	}

	void ShaderProgram::bindBuffers()
	{
		auto colors = vertices.getPalette().toArray4();
		auto points = vertices.getPointArray().toArray3();

		if (vertex_array != 0) {
			glDeleteVertexArrays(1, &vertex_array);
		}
		if (vbos[0] != 0) {
			glDeleteBuffers(1, &vbos[0]);
			vbos[0] = 0;
		}
		if (vbos[1] != 0) {
			glDeleteBuffers(1, &vbos[1]);
			vbos[1] = 0;
		}
		glGenBuffers(2, vbos);
		glGenVertexArrays(1, &vertex_array);
		glBindVertexArray(vertex_array);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
		glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(PointArray::value_type::value_type) * points.size(), 
			points.data(),
			ShaderData::toBufferAllocationType((at(0).getBufferAllocType()))
		);
		glVertexAttribPointer(
			0, 
			PointArray::value_type::length(), 
			GL_FLOAT, 
			GL_FALSE, 
			0, 
			nullptr
		);

		glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
		glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(Palette::value_type::value_type) * colors.size(), 
			colors.data(),
			ShaderData::toBufferAllocationType((at(1).getBufferAllocType()))
		);
		glVertexAttribPointer(
			1, 
			Palette::value_type::length(), 
			GL_FLOAT, 
			GL_FALSE, 
			0, 
			nullptr
		);
	}
	void ShaderProgram::build()
	{
		if (size() == 0)
			return;
		for (auto &shader : *this)
			if (!shader.compile())
				return;
		attach();
		link();

		bindBuffers();
	}

	void ShaderProgram::attach() const
	{
		for (auto &shader : *this) 
		{
			glAttachShader(program, shader.getDescriptor());
		}
	}

	void ShaderProgram::render() const
	{
		glUseProgram(program);
		glBindVertexArray(vertex_array);
		glDrawArrays(toDrawAlgorithm(draw_algorithm), 0, vertices.size());
	}

	void ShaderProgram::link() const
	{
		glLinkProgram(program);
	}

	void ShaderProgram::setVertexCount(size_t count)
	{
		vertices.resize(count);
	}

	ShaderProgram::PrimitiveType ShaderProgram::getPrimitiveType() const 
	{
		return draw_algorithm;
	}

	void ShaderProgram::setPrimitiveType(PrimitiveType type) 
	{
		draw_algorithm = type;
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
