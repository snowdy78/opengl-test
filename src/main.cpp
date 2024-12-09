#include <vector>
#include <string>
#include "SGL/SGL.hpp"
static std::string vertex_shader = R"(
#version 460
layout (location = 0) in vec3 vpos;
layout (location = 1) in vec3 vcolor;
out vec3 outColor;
void main()
{
    gl_Position = vec4(vpos, 1.0);
    outColor = vcolor;
}
)";
static std::string fragment_shader = R"(
#version 460
in vec3 outColor;
out vec4 fragColor;
void main()
{
    fragColor = vec4(outColor, 1.0);
}
)";
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
    ShaderBuildSystem shader{vertex_shader, fragment_shader};

    shader.setPoints(points.begin(), points.end());
    shader.setPalette(colors.begin(), colors.end());
    shader.build();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (window.isOpen())
    {
        window.clear();
        shader.render();
        shader.draw();
        window.display();
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}