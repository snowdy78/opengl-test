#include <iostream>
#include "SGL/SGLdecl.hpp"



namespace sgl
{
    void init()
    {
        if (!glfwInit())
        {
            exit(EXIT_FAILURE);
        }
    }
}

