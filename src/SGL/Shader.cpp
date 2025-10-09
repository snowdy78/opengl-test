#include "SGL/Shader.hpp"
#include "SGL/ShaderData.hpp"

namespace sgl
{
	Shader::Shader(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
	{
		ShaderData vertex_shader(ShaderData::Vertex);
		vertex_shader.setCode(getFileData(vertex_shader_code));
		ShaderData fragment_shader(ShaderData::Fragment);
		fragment_shader.setCode(getFileData(fragment_shader_code));
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
	void Shader::setPrimitiveType(ShaderProgram::PrimitiveType type)
	{
		program.setPrimitiveType(type);
	}
	ShaderProgram::PrimitiveType Shader::getPrimitiveType() const
	{
		return program.getPrimitiveType();
	}
} // namespace sgl
