#pragma once

#include "SGL/SGLdecl.hpp"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
namespace sgl
{
	class Transform
	{
	public:
		struct RotationAxis
		{
			glm::vec<3, bool> xyz;
			RotationAxis(bool x = true, bool y = false, bool z = false)
				: xyz{ x, y, z }
			{}
		};

	private:
		glm::mat4 _transform;
		Component *_component = nullptr;
		glm::vec3 pos{};
		glm::vec3 scale_factor{ 1.0, 1.0, 1.0 };
		float rotation{ 0.0 };
		RotationAxis rotation_axis{};
		mutable bool need_update = true;

		static glm::mat4 initMatrix();

	public:
		Transform();
		Transform(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);
		void bind(Component *component);
		void translate(const glm::vec3 &vec);
		void scale(const glm::vec3 &vec);
		void rotate(float angle, const RotationAxis &axis = {});
		glm::vec3 getPosition() const;
		glm::vec3 getScale() const;
		float getRotation() const;
		glm::vec3 transformPoint(const glm::vec3 &point) const;
		const glm::mat4 &getMatrix() const;
		bool isNeedUpdate() const;
		void update();
	};
} // namespace sgl
