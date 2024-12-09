#include "SGL/Window.hpp"
#include <stdexcept>
#include <iostream>

namespace sgl
{

    Window::Window(int width, int height, const char* title)
    {
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            throw std::runtime_error("Failed to create Window");
        }
        glfwMakeContextCurrent(window);
        
        if (!gladLoadGL())
        {
            std::cout << "Cannot to load GLAD" << std::endl;
        }
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
    bool Window::isOpen() const
    {
        return !glfwWindowShouldClose(window);
    }

}
