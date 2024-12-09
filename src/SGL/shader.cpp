#include "SGL/shader.hpp"

namespace sgl
{
	ShaderBuildSystem::ShaderBuildSystem(const std::string &vertex_shader_code, const std::string &fragment_shader_code)
		: vertex_shader(Shader::Vertex, vertex_shader_code),
		  fragment_shader(Shader::Fragment, fragment_shader_code)
	{}
	void ShaderBuildSystem::build(ShaderProgram &program)
	{
		vertex_shader.compile();
		fragment_shader.compile();
		program.attach(vertex_shader);
		program.attach(fragment_shader);
		program.link();

		vertex_shader.remove();
		fragment_shader.remove();

		program.bindBuffers();
	}
	ShaderBuildSystem::~ShaderBuildSystem()
	{
		delete program;
	}

	void ShaderBuildSystem::draw()
	{
		if (program)
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}

} // namespace sgl
