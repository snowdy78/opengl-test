#include "SGL/Color.hpp"

namespace sgl
{

	Color::Color(const value_type &r, const value_type &g, const value_type &b, const value_type &a)
		: glm::vec4(r, g, b, a)
	{}

} // namespace sgl
