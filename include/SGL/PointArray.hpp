#pragma once

#include "SGL/SGLdecl.hpp"
#include <vector>

namespace sgl
{
    class PointArray : public std::vector<Point>
    {
    public:
        using std::vector<Point>::vector;
        const Point *ptr() const noexcept
		{
            if (empty())
                return nullptr;
			return &at(0);
		}
    };
}