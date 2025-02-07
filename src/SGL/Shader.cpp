#include "SGL/Shader.hpp"

namespace sgl
{
	Shader::Shader(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
	{
		ShaderData vertex_shader;
		vertex_shader.load(vertex_shader_code, ShaderData::Vertex);
		ShaderData fragment_shader;
		fragment_shader.load(fragment_shader_code, ShaderData::Fragment);
		emplace_back(std::move(vertex_shader));
		emplace_back(std::move(fragment_shader));
	}

	void Shader::draw() const
	{
        render();
	}

} // namespace sgl
