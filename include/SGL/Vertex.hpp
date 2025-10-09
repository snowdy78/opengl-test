#pragma once


#include "SGL\SGLfwd.hpp"
#include "Color.hpp"
#include <glm/vec3.hpp>

namespace sgl
{
	struct Vertex
	{
		glm::vec3 position;
		Color color;

	public:
		Vertex() = default;
		Vertex(const glm::vec3 position, const Color &color = Color::white)
			: position(position),
			  color(color)
		{}
	};
} // namespace sgl
