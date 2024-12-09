#pragma once

#include <vector>
#include "SGLdecl.hpp"

#include "ShaderData.hpp"

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
		bool need_render	   = false;
		GLuint points_vbo	   = 0;
		GLuint colors_vbo	   = 0;
		GLuint vao			   = 0;
		glm::mat3 point_mat3;
		glm::mat3 color_mat3;

	public:
		ShaderProgram() {}
		ShaderProgram(const ShaderProgram &)			= delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;
		~ShaderProgram();
		void bindBuffers();
		void attach(ShaderData &shader);
		void render();
		void link();
		void setPoints(const glm::mat3 &mat3);
		void setPalette(const glm::mat3 &mat3);
	};

} // namespace sgl
