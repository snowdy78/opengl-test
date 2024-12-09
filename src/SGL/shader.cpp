#include "SGL/Shader.hpp"

namespace sgl
{

	Shader::Shader(ShaderType type, const std::string &shader_code)
		: type(type)
	{
		code = (char *) malloc(shader_code.size() + 1);
		code[shader_code.size()] = '\0';
		for (int s = 0; s != strlen(code); ++s)
		{

			code[s] = shader_code[s];
		}

		shader = glCreateShader(type == Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		glShaderSource(shader, 1, &code, nullptr);
	}

	Shader::~Shader()
	{
		delete[] code;
	}

	GLuint &Shader::operator*()
	{
		return shader;
	}

	const GLuint &Shader::operator*() const
	{
		return shader;
	}

	Shader::ShaderType Shader::getType() const
	{
		return type;
	}
	void Shader::compile()
	{
		glCompileShader(shader);
	}

	void Shader::remove()
	{
		glDeleteShader(shader);
	}
} // namespace sgl
