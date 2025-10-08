#pragma once

#include <functional>
#include "Color.hpp"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "SGL/Math/Area.hpp"


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
		glm::ivec2 getSize() const;
		bool isOpen() const;
		void clear(const Color &color = Color::black);
		void clearArea(const area2d<float> &area, const Color &color = Color::black);
		void draw(const Drawable &drawable) const;
		void update() const;
		void setMSAA(bool value);

		void setMouseMoveCallback(const std::function<void(const glm::vec2 &)> &callback);
	};
} // namespace sgl
