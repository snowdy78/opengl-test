#include "SGL/Window.hpp"
#include <stdexcept>
#include <iostream>
#include "SGL/Drawable.hpp"

namespace sgl
{
	Window::Window(const glm::ivec2 &size, const char *title)
	{
		constexpr static int samples = 4; // TODO change sample count
		glfwWindowHint(GLFW_SAMPLES, samples);
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

	void Window::clearArea(const area2d<float> &area, const Color &color)
	{
		auto converted = area.convert<GLint>();
		glEnable(GL_SCISSOR_TEST);
		glScissor(converted.left, converted.top, converted.width, converted.height);
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT);
		glDisable(GL_SCISSOR_TEST);
	}
	void Window::draw(const Drawable &drawable) const
	{
		drawable.draw();
	}
	void Window::update() const
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

	glm::ivec2 Window::getSize() const
	{
		glm::ivec2 size;
		glfwGetWindowSize(window, &size.x, &size.y);
		return size;
	}
	void Window::setMSAA(bool value)
	{
		if (value)
		{
			glEnable(GL_MULTISAMPLE);
		}
		else
		{
			glDisable(GL_MULTISAMPLE);
		}
	}
} // namespace sgl
