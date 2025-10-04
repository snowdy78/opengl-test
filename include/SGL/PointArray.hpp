#pragma once

#include "SGL/SGLdecl.hpp"
#include <vector>

namespace sgl
{
	class PointArray : public std::vector<Point>
	{
	public:
		using std::vector<Point>::vector;
		std::vector<glm::vec3::value_type> toArray3() const noexcept
		{
			std::vector<glm::vec3::value_type> matrix;
			for (auto &point: *this)
			{
				matrix.push_back(point.x);
				matrix.push_back(point.y);
				matrix.push_back(point.z);
			}
			return matrix;
		}
		const Point *ptr() const noexcept
		{
			if (empty())
				return nullptr;
			return &at(0);
		}
	};
} // namespace sgl
