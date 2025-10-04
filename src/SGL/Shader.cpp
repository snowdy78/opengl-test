#include "SGL/Shader.hpp"
#include "SGL/ShaderData.hpp"

namespace sgl
{
	Shader::Shader(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
	{
		ShaderData vertex_shader;
		vertex_shader.load(vertex_shader_code, ShaderData::Vertex);
		ShaderData fragment_shader;
		fragment_shader.load(fragment_shader_code, ShaderData::Fragment);
		program.emplace_back(std::move(vertex_shader));
		program.emplace_back(std::move(fragment_shader));
		program.transform.bind(this);
		program.build();
	}

	void Shader::draw() const
	{
		program.render();
	}
	void Shader::setVertex(size_t i, const Vertex &vertex)
	{
		program.setVertex(i, vertex);
	}
	void Shader::onTransformUpdate()
	{
		program.build();
	}
} // namespace sgl
