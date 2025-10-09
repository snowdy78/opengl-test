#pragma once

#include "SGL\SGLfwd.hpp"
#include <glm/vec2.hpp>

namespace sgl
{
	template<class T>
	struct area2d
	{
		T left, top, width, height;
		area2d(const T &left, const T &top, const T &width, const T &height)
			: left(left),
			  top(top),
			  width(width),
			  height(height)
		{}
		bool contains(const glm::vec2 &point)
		{
			return point.x >= left && point.x <= left + width && point.y >= top && point.y <= top + height;
		}
		template<class X>
		area2d<X> convert() const
		{
			return area2d<X>(static_cast<X>(left), static_cast<X>(top), static_cast<X>(width), static_cast<X>(height));
		}
	};
} // namespace sgl
