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
        shader.setVertex(0, {points[i], colors[i]});
    }
    shader.build();
    window.setMouseMoveCallback([&](const glm::vec2 &pos) {
        auto x = pos.x/window.getSize().x * 2.0 - 1.0;
        auto y = pos.y/window.getSize().y * 2.0 - 1.0;
        glm::vec2 p{ x, -y };
        std::cout << points[0][0] << " " << points[0][1] << std::endl;
        Vertex v(shader.getVertex(0));
        v.position = {p, 0};
        shader.setVertex(0, v);
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