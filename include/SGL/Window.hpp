#pragma once

#include "SGL/SGLdecl.hpp"
#include "Color.hpp"


namespace sgl
{
	class Window
	{
		GLFWwindow *window;
		Color color;

	public:
		Window(int width, int height, const char *title);
		~Window();
		bool isOpen() const;
		void clear(const Color &color = Color::black);
		void display();
	};
}
