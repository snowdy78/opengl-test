#include "SGL/Transform.hpp"

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

	void Transform::translate(const glm::vec3 &vec)
	{
		_transform = glm::translate(_transform, vec);
	}

	void Transform::scale(const glm::vec3 &vec)
	{
		_transform = glm::scale(_transform, vec);
	}

	void Transform::rotate(float angle, const glm::vec3 &relative)
	{
		_transform = glm::rotate(_transform, angle, relative);
	}

	const glm::mat4 &Transform::getMatrix() const
	{
		return _transform;
	}

} // namespace sgl
