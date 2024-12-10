#pragma once

#include <vector>
#include "SGLdecl.hpp"

#include "ShaderData.hpp"
#include "VertexArray.hpp"


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
		VertexArray vertices;

	public:
		ShaderProgram() {}
		ShaderProgram(const ShaderProgram &)			= delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;
		~ShaderProgram();
		void bindBuffers();
		void attach(ShaderData &shader);
		void render();
		void link();
		void setVertexCount(size_t count);
		Vertex &getVertex(size_t i);
		const Vertex &getVertex(size_t i) const;
	};

} // namespace sgl
