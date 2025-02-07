#include "SGL/SGLdecl.hpp"



namespace sgl
{
    int init()
    {
        if (!glfwInit())
        {
            exit(EXIT_FAILURE);
            return 0;
        }
        return 1;
    }
}

