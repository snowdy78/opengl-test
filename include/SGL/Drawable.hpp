#pragma once

#include "SGL\SGLfwd.hpp"

namespace sgl
{
	class Drawable
	{
	public:
		virtual ~Drawable()		  = 0;
		virtual void draw() const = 0;
	};
} // namespace sgl
