#pragma once

#include <string>
#include "SGLdecl.hpp"


#include "Component.hpp"
#include "ShaderData.hpp"
#include "ShaderProgram.hpp"


namespace sgl
{
	class Shader : public ShaderProgram, public Component
	{
		ShaderData vertex_shader;
		ShaderData fragment_shader;
		class PositionLayout : public ShaderData::LayoutValue
		{
		public:
			using ShaderData::LayoutValue::LayoutValue;

			const glm::vec3 &getPosition() const
			{
				return *(glm::vec3 *) value;
			}
			virtual size_t getSizeInBytes() override
			{
				return sizeof(glm::vec3);
			}
		};
		class ColorLayout : public ShaderData::LayoutValue
		{
		public:
			using ShaderData::LayoutValue::LayoutValue;

			const Color &getColor() const
			{
				return *(Color *) value;
			}
			virtual size_t getSizeInBytes() override
			{
				return sizeof(Color);
			}

		};

	public:
		using Component::transform;
		Shader(const std::string &path_to_vertex_shader, const std::string &path_to_fragment_shader);
		void build();
		void draw() const override;
		void setVertexCount(size_t count);
		void setVertex(size_t vertex_id, const Vertex &vertex);
	};

} // namespace sgl
