#pragma once

#include <string>
#include "SGL/VertexArray.hpp"
#include "SGL/SGLfwd.hpp"
#include "SGL/Component.hpp"
#include "ShaderProgram.hpp"


namespace sgl
{
	class BasicShader : public Component
	{
		ShaderProgram program;

	public:
		BasicShader(const std::string &path_to_vertex_shader, const std::string &path_to_fragment_shader);
		void setVertex(size_t i, const Vertex &vertex);
		void assignVertices(const VertexArray &vertex_array);
		void setPrimitiveType(ShaderProgram::PrimitiveType type);
		ShaderProgram::PrimitiveType getPrimitiveType() const;
		void draw() const override;

	protected:
		void onTransformUpdate() final;
	};

} // namespace sgl
