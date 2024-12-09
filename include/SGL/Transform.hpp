#pragma once

#include "SGL/SGLdecl.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace sgl
{
	class Transform
	{
		glm::mat4 _transform;
		Component *_component = nullptr;

	public:
		Transform();
		Transform(
			const float &left, const float &right, const float &bottom, const float &top, const float &nearVal,
			const float &farVal
		);
		void bind(Component *component);
		void translate(const glm::vec3 &vec);
		void scale(const glm::vec3 &vec);
		void rotate(float angle, const glm::vec3 &relative);
		const glm::mat4 &getMatrix() const;
	};
} // namespace sgl
