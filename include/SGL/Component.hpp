#pragma once

#include "Drawable.hpp"
#include "SGL/SGLdecl.hpp"
#include "Transform.hpp"


namespace sgl
{
	class Component : public Drawable
	{
    protected:
		Transform transform;

	public:
		Component()
		{
		    transform.bind(this);
		}
        virtual void onTransformUpdate() {}
        virtual void onTranslate() {}
        virtual void onScale() {}
        virtual void onRotate() {}
        virtual ~Component() = default;
	};
} // namespace sgl
