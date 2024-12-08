#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
int main()
{
    GLFWwindow* window;
    GLfloat points[] = {
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
    };
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(600, 800, "My Window", nullptr, nullptr);
    if (!window)
    {
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL())
    {
        std::cout << "Cannot to load GLAD" << std::endl;
    }
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char *vsh = vertex_shader.c_str();
    glShaderSource(vs, 1, &vsh, nullptr);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fsh = fragment_shader.c_str();
    glShaderSource(fs, 1, &fsh, nullptr);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}