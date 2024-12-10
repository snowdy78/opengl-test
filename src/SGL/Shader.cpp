#include "SGL/Shader.hpp"
#include <vector>

namespace sgl
{
	Shader::Shader(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
	{
		vertex_shader.load(vertex_shader_code, ShaderData::Vertex);
		fragment_shader.load(fragment_shader_code, ShaderData::Fragment);
		vertex_shader.setLayoutCount(2);
	}
	void Shader::build()
	{
		if (!vertex_shader.compile())
			return;
		if (!fragment_shader.compile())
			return;
		attach(vertex_shader);
		attach(fragment_shader);
		link();

		bindBuffers();
	}

	void Shader::draw() const
	{
        const_cast<ShaderProgram &>(static_cast<const ShaderProgram &>(*this)).render();
		glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
	}

	void Shader::setVertexCount(size_t count)
	{
		vertices.resize(count);
	}
	void Shader::setVertex(size_t vertex_id, const Vertex &vertex)
	{
		vertices[vertex_id] = vertex;
		vertex_shader.setLayoutValue(0, vertex_id, &vertices[vertices.size() - 1].position[0]);
		vertex_shader.setLayoutValue(1, vertex_id, &vertices[vertices.size() - 1].color[0]);
	}
} // namespace sgl
