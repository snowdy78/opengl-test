#include "SGL/BasicShader.hpp"
#include "SGL/ShaderData.hpp"

namespace sgl
{
	BasicShader::BasicShader(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
	{
		ShaderData vertex_shader(ShaderData::Vertex);
		vertex_shader.setCode(getFileData(vertex_shader_code));
		ShaderData fragment_shader(ShaderData::Fragment);
		fragment_shader.setCode(getFileData(fragment_shader_code));
		program.push_back(std::move(vertex_shader));
		program.push_back(std::move(fragment_shader));
		program.build();
	}

	void BasicShader::draw() const
	{
		if (transform.isNeedUpdate())
			transform.update();
		program.render();
	}
	void BasicShader::setVertex(size_t i, const Vertex &vertex)
	{
		program.setVertex(i, vertex);
	}
	void BasicShader::onTransformUpdate()
	{
		program.transformPoints([this](const glm::vec3 &point) {
			return transform.transformPoint(point);
		});
		program.build();
	}
	void BasicShader::setPrimitiveType(ShaderProgram::PrimitiveType type)
	{
		program.setPrimitiveType(type);
	}
	ShaderProgram::PrimitiveType BasicShader::getPrimitiveType() const
	{
		return program.getPrimitiveType();
	}
	void BasicShader::assignVertices(const VertexArray &vertex_array)
	{
		program.assignVertices(vertex_array);
	}
} // namespace sgl
