#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL/gl.h>

namespace sgl
{
    class Window;
    class Color;

    struct Shader;
    class ShaderProgram;
    class ShaderBuildSystem;
    class Drawable;
    class Transform;
    class Component;
    using Point = glm::vec3;
    void init();
}
