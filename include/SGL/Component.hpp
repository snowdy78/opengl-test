#pragma once

#include "Drawable.hpp"
#include "SGL\SGLfwd.hpp"
#include "Transform.hpp"


namespace sgl
{
	class Component : public Drawable
	{
	public:
		Component() {}
		virtual ~Component() = 0;

	protected:
		friend void Transform::update();
		virtual void onTransformUpdate() {}
	};
	inline Component::~Component() = default;
} // namespace sgl
