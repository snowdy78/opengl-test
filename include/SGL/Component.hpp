#pragma once

#include "Drawable.hpp"
#include "SGL/SGLdecl.hpp"
#include "Transform.hpp"


namespace sgl
{
	class Component : public Drawable
	{
	public:
		Component()
		{
		}
        virtual void onTransformUpdate() {}
        virtual ~Component() = 0;
	};
	inline Component::~Component() = default;
} // namespace sgl
