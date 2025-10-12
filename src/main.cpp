#include <string>
#include "SGL/SGL.hpp"
#include <iostream>
#include <glm/glm.hpp>

using namespace sgl;
int main()
{
	auto vertices = VertexArray{
		{ { 0.0f, 0.5f, 0.0f },	{ 1.0f, 0.0f, 0.0f } },
		 { { -0.5f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f } },
		{ { 0.0f, -1.0f, 0.0f },	 { 0.0f, 0.0f, 0.0f } },
		 { { 0.5f, -0.5f, 0.0f },  { 1.0f, 0.0f, 0.0f } },
		{ { 0.0f, 0.5f, 0.0f },	{ 1.0f, 0.0f, 0.0f } },
	};
	Window window({ 800, 600 }, "Triangle");
	window.setMSAA(true);
	BasicShader shader{ "triangle.vert", "triangle.frag" };
	BasicShader shader2{ "triangle.vert", "triangle.frag" };
	shader2.assignVertices(vertices);
	shader.assignVertices(vertices);
	shader.transform.translate({ 0.2f, 0.0f, 0.0f });
	// TODO rework transform
	while (window.isOpen())
	{
		window.clear({ 0.1, 0.2, 0.3, 1.0 });
		window.draw(shader);
		shader.transform.translate({ 0.2f, 0.0f, 0.0f });
		window.draw(shader2);
		window.update();
		glfwPollEvents();
	}
	return 0;
}
