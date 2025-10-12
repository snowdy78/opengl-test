#include "SGL/ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "SGL/Graphics/vertex_array_object.hpp"

namespace sgl
{
	ShaderProgram::ShaderProgram() {}
	void ShaderProgram::makeBuild() const
	{
		if (size() == 0)
			return;
		for (auto &shader: m_shaders)
		{
			if (!shader.compile())
				return;
			shader.attach(*this);
		}
		link();
		updateBuffers();
		need_build = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(program);
	}
	void ShaderProgram::updateBuffers() const
	{
		std::cout << "build\n";
		m_vao.gen();
		m_vao.bind();
		for (auto &shader: m_shaders)
		{
			switch (shader.getType())
			{
				case sgl::ShaderData::Vertex:
					shader.clearBuffers();
					shader.pushBuffer(
						sgl::buffer(sgl::buffer::Array, sgl::buffer::StaticDraw, m_vao.dataPoints(), m_vao.lenPoints()),
						sgl::layout(0, vertex_array_object::pointSize())
					);
					shader.pushBuffer(
						sgl::buffer(sgl::buffer::Array, sgl::buffer::StaticDraw, m_vao.dataColors(), m_vao.lenColors()),
						sgl::layout(1, vertex_array_object::colorSize())
					);
					shader.build();
					break;
				default:
					break;
			}
		}
		m_vao.unbind();
	}
	void ShaderProgram::build() const
	{
		need_build = true;
	}

	void ShaderProgram::render() const
	{
		if (need_build)
		{
			makeBuild();
		}
		glUseProgram(program);
		m_vao.bind();
		glDrawArrays(draw_algorithm, 0, m_vao.getVertexCount());
		m_vao.unbind();
	}

	void ShaderProgram::link() const
	{
		glLinkProgram(program);
	}

	size_t ShaderProgram::getVertexCount() const
	{
		return m_vao.getVertexCount();
	}

	ShaderProgram::PrimitiveType ShaderProgram::getPrimitiveType() const
	{
		return draw_algorithm;
	}

	void ShaderProgram::setPrimitiveType(PrimitiveType type)
	{
		draw_algorithm = type;
	}
	Vertex ShaderProgram::getVertex(size_t i) const
	{
		return m_vao.vertex(i);
	}
	void ShaderProgram::setVertex(size_t i, const Vertex &vertex)
	{
		m_vao.vertex(i, vertex);
		build();
	}
	void ShaderProgram::assignVertices(const VertexArray &vertex_array)
	{
		m_vao.assign(vertex_array);
		build();
	}
	void ShaderProgram::addVertex(const Vertex &vertex)
	{
		m_vao.push_back(vertex);
		build();
	}
	void ShaderProgram::insertVertex(size_t index, const Vertex &vertex)
	{
		m_vao.insert(index, vertex);
		build();
	}
	void ShaderProgram::emplace_back(ShaderData::Type type)
	{
		m_shaders.emplace_back(type);
	}
	void ShaderProgram::push_back(ShaderData &&shader_data)
	{
		m_shaders.push_back(std::move(shader_data));
	}
	size_t ShaderProgram::size() const
	{
		return m_shaders.size();
	}
	void ShaderProgram::clear()
	{
		m_shaders.clear();
	}
	void ShaderProgram::transformPoints(std::function<glm::vec3(const glm::vec3 &)> transformation_func)
	{
		m_vao.transformPoints(transformation_func);
	}
} // namespace sgl
