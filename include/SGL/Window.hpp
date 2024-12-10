#pragma once

#include <functional>
#include "Color.hpp"
#include "SGL/SGLdecl.hpp"


namespace sgl
{
	class Window
	{
		friend class Callback;

		GLFWwindow *window;
		Color color;
		std::function<void(const glm::vec2 &)> mouse_move_callback = [](const glm::vec2 &) {};

	public:
		enum Callback
		{
			MouseMove, /* add other callbacks */
		};
		Window(const glm::ivec2 &size, const char *title);
		~Window();
		glm::ivec2 getSize() const
		{
			glm::ivec2 size;
			glfwGetWindowSize(window, &size.x, &size.y);
			return size;
		}
		bool isOpen() const;
		void clear(const Color &color = Color::black);
		void display();

		void setMouseMoveCallback(const std::function<void(const glm::vec2 &)> &callback);
	};
} // namespace sgl
