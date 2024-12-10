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
    glm::mat3 colors {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };
    Shader shader{"triangle.vert", "triangle.frag"};

    shader.setPoints(points);
    shader.setPalette(colors);
    shader.build();
    window.setMouseMoveCallback([&](const glm::vec2 &pos) {
        points[0][0] = pos.x/window.getSize().x * 2.0 - 1.0;
        points[0][1] = -pos.y/window.getSize().y * 2.0 + 1.0;
        std::cout << points[0][0] << " " << points[0][1] << std::endl;
        shader.setPoints(points);
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