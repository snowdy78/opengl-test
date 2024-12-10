#include "SGL/Window.hpp"
#include <stdexcept>
#include <iostream>

namespace sgl
{

    Window::Window(const glm::ivec2 &size, const char* title)
    {
        window = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr);
        if (!window)
        {
            throw std::runtime_error("Failed to create Window");
        }
        glfwMakeContextCurrent(window);
        
        if (!gladLoadGL())
        {
            std::cout << "Cannot to load GLAD" << std::endl;
        }
        glfwSetWindowUserPointer(window, this);
        glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
            Window *pw = (Window *) glfwGetWindowUserPointer(window);
            pw->mouse_move_callback({ x, y });
        });
    }

    Window::~Window()
    {
        glfwDestroyWindow(window);
    }

    void Window::clear(const Color &color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    void Window::display()
    {
        glfwSwapBuffers(window);
    }
    void Window::setMouseMoveCallback(const std::function<void(const glm::vec2 &)> &callback)
    
    {
    
    	mouse_move_callback = callback;
    
    }
    bool Window::isOpen() const
    {
        return !glfwWindowShouldClose(window);
    }

}
