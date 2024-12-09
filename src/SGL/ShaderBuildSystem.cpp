#include "SGL/ShaderBuildSystem.hpp"
#include "SGL/ShaderProgram.hpp"

namespace sgl
{
	ShaderBuildSystem::ShaderBuildSystem(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
	{
		vertex_shader.load(vertex_shader_code, Shader::Vertex);
		fragment_shader.load(fragment_shader_code, Shader::Fragment);
	}
	void ShaderBuildSystem::build()
	{
		if (!vertex_shader.compile())
			return;
		if (!fragment_shader.compile())
			return;
		attach(vertex_shader);
		attach(fragment_shader);
		link();

		vertex_shader.remove();
		fragment_shader.remove();

		bindBuffers();
	}

	void ShaderBuildSystem::draw() const
	{
        const_cast<ShaderProgram &>(static_cast<const ShaderProgram &>(*this)).render();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

} // namespace sgl
