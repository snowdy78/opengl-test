#include "SGL/Shader.hpp"

namespace sgl
{
	Shader::Shader(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
	{
		vertex_shader.load(vertex_shader_code, ShaderData::Vertex);
		fragment_shader.load(fragment_shader_code, ShaderData::Fragment);
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
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

} // namespace sgl
