#include <string>
#include <iostream>
#include "SGL/SGL.hpp"

using namespace sgl;
int main()
{
    init();
    Window window({800, 600}, "OpenGL");
	glm::mat3 points(
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f
	);
    Palette colors {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
    };
    Shader shader{"triangle.vert", "triangle.frag"};

    shader.setVertexCount(3);
    for (size_t i = 0; i < points.length(); i++)
    {
        shader.getVertex(i).position = points[i];
    }
    for (size_t i = 0; i < points.length(); i++)
    {
        shader.getVertex(i).color = colors[i];
    }
    shader.getVertex(0).position = points[0];
    shader.build();
    window.setMouseMoveCallback([&](const glm::vec2 &pos) {
        glm::vec2 p{ pos.x/window.getSize().x * 2.0 - 1.0, -pos.y/window.getSize().y * 2.0 + 1.0};
        std::cout << points[0][0] << " " << points[0][1] << std::endl;
        shader.getVertex(0).position = {p, 0};
        shader.build();
    });

    while (window.isOpen())
    {
		window.clear({0.0f, 1.0f, 0.0f, 1.0f});
		shader.draw();
		window.display();
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}