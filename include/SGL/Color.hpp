#pragma once

#include "SGL/SGLdecl.hpp"
#include <glm/vec4.hpp>
namespace sgl
{
	struct Color : glm::vec4
	{
	public:
		using value_type = glm::vec4::value_type;
		using glm::vec4::vec4;
		Color(const value_type &r, const value_type &g, const value_type &b);

		glm::vec3 simplify() const;
		static const Color black;
		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color yellow;
		static const Color magenta;
		static const Color cyan;
		static const Color transparent;
	};
} // namespace sgl
