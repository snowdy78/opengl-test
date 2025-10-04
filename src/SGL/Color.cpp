#include "SGL/Color.hpp"

namespace sgl
{
	const Color Color::black = Color(0, 0, 0);

	const Color Color::white = Color(1, 1, 1);

	const Color Color::red = Color(1, 0, 0);

	const Color Color::green = Color(0, 1, 0);

	const Color Color::blue = Color(0, 0, 1);

	const Color Color::yellow = Color(1, 1, 0);

	const Color Color::magenta = Color(1, 0, 1);

	const Color Color::cyan = Color(0, 1, 1);

	const Color Color::transparent = Color(0, 0, 0, 0);
	Color::Color(const value_type &r, const value_type &g, const value_type &b)
		: glm::vec4(r, g, b, 1.)
	{}

	glm::vec3 Color::simplify() const
	{
		return { r, g, b };
	}

} // namespace sgl
