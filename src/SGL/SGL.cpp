#include <stdexcept>
#include "..\..\include\SGL\SGLfwd.hpp"

namespace sgl
{
	GLFWINIT init()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
		return GLFWINIT();
	}
} // namespace sgl
