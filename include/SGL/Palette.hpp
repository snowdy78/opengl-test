#pragma once


#include <vector>
#include "SGL/Color.hpp"


namespace sgl
{
	class Palette : public std::vector<Color>
	{
	public:
		using std::vector<Color>::vector;
		const Color *ptr() const noexcept
		{
            if (empty())
                return nullptr;
			return &at(0);
		}
	};
} // namespace sgl
