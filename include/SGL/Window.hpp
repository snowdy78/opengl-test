#pragma once

#include "SGL/SGLdecl.hpp"

namespace sgl
{
	class Window
	{
		GLFWwindow *window;

	public:
		Window(int width, int height, const char *title);
		~Window();
		bool isOpen() const;
		void clear();
		void display();
	};
}
