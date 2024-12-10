#pragma once

#include "SGL/SGLdecl.hpp"

namespace sgl
{
	struct Color : glm::vec4
	{
	public:
		using value_type = glm::vec4::value_type;
		using glm::vec4::vec4;
		Color(const value_type &r, const value_type &g, const value_type &b, const value_type &a = 1);
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
	inline const Color Color::black = Color(0, 0, 0);

	inline const Color Color::white = Color(1, 1, 1);

	inline const Color Color::red = Color(1, 0, 0);

	inline const Color Color::green = Color(0, 1, 0);

	inline const Color Color::blue = Color(0, 0, 1);

	inline const Color Color::yellow = Color(1, 1, 0);

	inline const Color Color::magenta = Color(1, 0, 1);

	inline const Color Color::cyan = Color(0, 1, 1);

	inline const Color Color::transparent = Color(0, 0, 0, 0);
} // namespace sgl
