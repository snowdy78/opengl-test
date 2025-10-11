#include "SGL/Transform.hpp"
#include "SGL/Component.hpp"

#include "glm/ext/matrix_transform.hpp"

namespace sgl
{

	void Transform::update()
	{
		_transform	= initMatrix();
		_transform	= glm::translate(_transform, pos);
		_transform	= glm::scale(_transform, scale_factor);
		_transform	= glm::rotate(_transform, rotation, glm::vec3{ rotation_axis.xyz });
		need_update = false;
		if (_component != nullptr)
			_component->onTransformUpdate();
	}

	bool Transform::isNeedUpdate() const
	{
		return need_update;
	}

	glm::mat4 Transform::initMatrix()
	{
		return { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	}

	Transform::Transform()
		: _transform(initMatrix())
	{}

	Transform::Transform(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
		: _transform({ x1, y1, z1, 0, x2, y2, z2, 0, x3, y3, z3, 0, 0, 0, 0, 1 })
	{}

	void Transform::bind(Component *component)
	{
		_component = component;
	}

	void Transform::translate(const glm::vec3 &vec)
	{
		pos			= vec;
		need_update = true;
	}

	void Transform::scale(const glm::vec3 &vec)
	{
		scale_factor = vec;
		need_update	 = true;
	}

	void Transform::rotate(float angle, const RotationAxis &axis)
	{
		rotation	  = angle;
		rotation_axis = axis;
		need_update	  = true;
	}

	glm::vec3 Transform::getPosition() const
	{
		return pos;
	}

	glm::vec3 Transform::getScale() const
	{
		return scale_factor;
	}

	float Transform::getRotation() const
	{
		return rotation;
	}

	glm::vec3 Transform::transformPoint(const glm::vec3 &point) const
	{
		return glm::vec3{
			point.x * _transform[0].x + point.y * _transform[1].x + point.z * _transform[2].x + _transform[3].x,
			point.x * _transform[0].y + point.y * _transform[1].y + point.z * _transform[2].y + _transform[3].y,
			point.x * _transform[0].z + point.y * _transform[1].z + point.z * _transform[2].z + _transform[3].z
		};
	}

	const glm::mat4 &Transform::getMatrix() const
	{
		return _transform;
	}

} // namespace sgl
