#pragma once

#include <vector>
#include "SGLdecl.hpp"

#include "Shader.hpp"

namespace sgl
{
	class ShaderProgram
	{
		enum BufferType
		{
			Static,
			Dynamic
		};

	private:
		BufferType buffer_type = Static;
		GLuint program		   = glCreateProgram();
		GLuint points_vbo	   = 0;
		GLuint colors_vbo	   = 0;
		GLuint vao			   = 0;
		std::vector<GLfloat> point_mat3;
		std::vector<GLfloat> color_mat3;

	public:
		ShaderProgram() {}
		ShaderProgram(const ShaderProgram &)			= delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;
		void bindBuffers();
		void attach(Shader &shader);
		void render();
		void link();
		template<class It>
		void setPoints(It begin, const It &end);
		template<class It>
		void setPalette(It begin, const It &end);
	};

	template<class It>
	void ShaderProgram::setPoints(It begin, const It &end)
	{
		point_mat3.assign(begin, end);
	}

	template<class It>
	void ShaderProgram::setPalette(It begin, const It &end)
	{
		color_mat3.assign(begin, end);
	}
} // namespace sgl
