#pragma once

#include <string>
#include "SGL\SGLfwd.hpp"


#include "Component.hpp"
#include "ShaderProgram.hpp"


namespace sgl
{
	class Shader : public Component
	{
		ShaderProgram program;

	public:
		Transform &transform = program.transform;
		Shader(const std::string &path_to_vertex_shader, const std::string &path_to_fragment_shader);

		template<class Iterator>
		void assignVertices(Iterator begin, const Iterator &end)
		{
			program.assignVertices(begin, end);
		}
		void setVertex(size_t i, const Vertex &vertex);
		void setPrimitiveType(ShaderProgram::PrimitiveType type);
		ShaderProgram::PrimitiveType getPrimitiveType() const;
		void draw() const override;
		void onTransformUpdate() override;
	};

} // namespace sgl
