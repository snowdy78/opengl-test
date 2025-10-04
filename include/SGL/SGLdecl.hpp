#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <GL/gl.h>
// Welcome to SGL [Simple Graphics Library]
namespace sgl
{
	class Window;
	class Color;

	struct Shader;
	class ShaderProgram;
	class ShaderBuildSystem;
	class Drawable;
	class Transform;
	class Component;
	class Area;
	using Point = glm::vec3;
	class GLFWINIT
	{
	public:
		~GLFWINIT()
		{
			glfwTerminate();
		}
	};
	GLFWINIT init();
	inline static GLFWINIT initializer = init();
} // namespace sgl
