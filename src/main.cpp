#include <vector>
#include <string>
#include <iostream>
#include "SGL/SGL.hpp"

using namespace sgl;
int main()
{
    init();

    Window window(800, 600, "OpenGL");
    std::vector<GLfloat> points = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    std::vector<GLfloat> colors = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };
    ShaderBuildSystem shader{"triangle.vert", "triangle.frag"};

    shader.setPoints(points.begin(), points.end());
    shader.setPalette(colors.begin(), colors.end());
    shader.build();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (window.isOpen())
    {
        window.clear();
        shader.draw();
        window.display();
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}