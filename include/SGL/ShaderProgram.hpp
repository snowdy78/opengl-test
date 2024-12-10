#pragma once

#include <vector>
#include "SGLdecl.hpp"

#include "ShaderData.hpp"
#include "VertexArray.hpp"


namespace sgl
{
	class ShaderProgram
	{
	private:
		GLuint program	 = glCreateProgram();
		bool need_render = false;
		std::vector<ShaderData *> shaders;

	protected:
		VertexArray vertices{};

	public:
		ShaderProgram();
		ShaderProgram(const ShaderProgram &)			= delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;
		~ShaderProgram();
		void bindBuffers();
		void attach(ShaderData &shader);
		void detach(ShaderData &shader);
		void render();
		void link();
		const Vertex &getVertex(size_t i) const;
		size_t getVertexCount() const;
		ShaderData &shader(size_t index);
		const ShaderData &shader(size_t index) const;
		size_t getShaderCount() const;
	};

} // namespace sgl
