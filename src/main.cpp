#include <string>
#include "SGL/PointArray.hpp"
#include "SGL/SGL.hpp"
#include "SGL/SGLdecl.hpp"
#include "SGL/ShaderProgram.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace sgl;
int main()
{
    GLFWwindow* window;
    auto vertices = VertexArray{
        {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
        {{0.0f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
    };
    window = glfwCreateWindow(800, 600, "My Window", nullptr, nullptr);
    if (!window)
    {
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL())
    {
        std::cout << "Cannot to load GLAD" << std::endl;
    }
    
    ShaderData vsx;
    ShaderData fsx;
    if (!vsx.load("triangle.vert", ShaderData::Vertex) || !fsx.load("triangle.frag", ShaderData::Fragment))
    {
        std::cout << "Failed to load shaders" << std::endl;
        exit(EXIT_FAILURE);
    }
    vsx.compile();
    fsx.compile();
    ShaderProgram program;
    program.emplace_back(std::move(vsx));
    program.emplace_back(std::move(fsx));
    program.assignVertices(vertices.begin(), vertices.end());
    program.setPrimitiveType(ShaderProgram::PrimitiveType::TriangleFan);
    program.build();
    while (!glfwWindowShouldClose(window))
    {
        program.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}