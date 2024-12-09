#include <string>
#include "SGL/SGL.hpp"

using namespace sgl;
int main()
{
    init();
    Window window(800, 600, "OpenGL");
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