#include "SGL/Transform.hpp"
#include "SGL/Component.hpp"

namespace sgl
{

	Transform::Transform()
		: _transform(0.f)
	{}

	Transform::Transform(
		const float &left, const float &right, const float &bottom, const float &top, const float &nearVal,
		const float &farVal
	)
		: _transform(glm::frustum(left, right, bottom, top, nearVal, farVal))
	{}

	void Transform::bind(Component *component)
	{
		_component = component;
	}

	void Transform::translate(const glm::vec3 &vec)
	{
		_transform = glm::translate(_transform, vec);
        if (_component)
        {
            _component->onTransformUpdate();
            _component->onTranslate();
        }
	}

	void Transform::scale(const glm::vec3 &vec)
	{
		_transform = glm::scale(_transform, vec);
        if (_component)
        {
            _component->onTransformUpdate();
            _component->onScale();
        }
	}

	void Transform::rotate(float angle, const glm::vec3 &relative)
	{
		_transform = glm::rotate(_transform, angle, relative);
	    if (_component)
        {
            _component->onTransformUpdate();
            _component->onRotate();
        }
    }

	const glm::mat4 &Transform::getMatrix() const
	{
		return _transform;
	}

} // namespace sgl
