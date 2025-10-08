#include <string>
#include "SGL/SGL.hpp"

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
	Shader shader{ "triangle.vert", "triangle.frag" };
	Shader shader2{ "triangle.vert", "triangle.frag" };
	shader2.assignVertices(vertices.begin(), vertices.end());
	shader.assignVertices(vertices.begin(), vertices.end());

	// TODO rework transform
	shader.transform.translate({ 0.0, 0.5, 0.0 });
	shader.transform.rotate(3.14 / 4, { 0, 0, 1 });
	while (window.isOpen())
	{
		window.clear({ 0.1, 0.2, 0.3, 1.0 });
		window.draw(shader);
		window.draw(shader2);
		window.clearArea({ 0, 100, 400, 300 }, { 0.1, 0.2, 0.3, 1.0 });
		window.update();
		glfwPollEvents();
	}
	return 0;
}
