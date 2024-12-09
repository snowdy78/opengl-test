#include "SGL/ShaderBuildSystem.hpp"

namespace sgl
{
	ShaderBuildSystem::ShaderBuildSystem(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
		: vertex_shader(Shader::Vertex, vertex_shader_code),
		  fragment_shader(Shader::Fragment, fragment_shader_code)
	{}
	void ShaderBuildSystem::build()
	{
		vertex_shader.compile();
		fragment_shader.compile();
		attach(vertex_shader);
		attach(fragment_shader);
		link();

		vertex_shader.remove();
		fragment_shader.remove();

		bindBuffers();
	}

	void ShaderBuildSystem::draw()
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

} // namespace sgl
