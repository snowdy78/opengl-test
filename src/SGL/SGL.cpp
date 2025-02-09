#include <stdexcept>
#include "SGL/SGLdecl.hpp"

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
}

