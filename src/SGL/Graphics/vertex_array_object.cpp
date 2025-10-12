#include "SGL/Graphics/vertex_array_object.hpp"
#include "SGL/SGLfwd.hpp"

namespace sgl
{

	vertex_array_object::~vertex_array_object()
	{
		if (m_vertex_array != 0)
			del();
	}
	void vertex_array_object::gen() const
	{
		if (m_vertex_array != 0)
			del();
		glGenVertexArrays(1, &m_vertex_array);
	}
	void vertex_array_object::del() const
	{
		if (m_vertex_array == 0)
			return;
		glDeleteVertexArrays(1, &m_vertex_array);
		m_vertex_array = 0;
	}

	void vertex_array_object::bind() const
	{
		glBindVertexArray(m_vertex_array);
	}
	void vertex_array_object::assign(const VertexArray &vertex_array)
	{
		m_points	   = vertex_array.getPointArray().toArray3();
		m_colors	   = vertex_array.getPalette().toArray4();
		m_vertex_count = vertex_array.size();
	}
	void vertex_array_object::assign(const std::vector<Point> &points, Color general_color)
	{
		for (auto &point: points)
		{
			this->m_points.push_back(point.x);
			this->m_points.push_back(point.y);
			this->m_points.push_back(point.z);
			m_colors.push_back(general_color.r);
			m_colors.push_back(general_color.g);
			m_colors.push_back(general_color.b);
			m_colors.push_back(general_color.a);
			m_vertex_count++;
		}
	}

	void vertex_array_object::transformPoints(const std::function<glm::vec3(const glm::vec3 &)> &transformation_func)
	{
		for (size_t i = 0; i < m_points.size(); i += pointSize())
		{
			auto &x = m_points[i], &y = m_points[i + 1], &z = m_points[i + 2];
			auto point = transformation_func({ m_points[i], m_points[i + 1], m_points[i + 2] });
			x		   = point.x;
			y		   = point.y;
			z		   = point.z;
		}
	}
	void vertex_array_object::setVertexColor(size_t vertex, Color color)
	{
		auto cpos		   = vertex * colorSize();
		m_colors[cpos]	   = color.r;
		m_colors[cpos + 1] = color.g;
		m_colors[cpos + 2] = color.b;
		m_colors[cpos + 3] = color.a;
	}
	size_t vertex_array_object::getVertexCount() const noexcept
	{
		return m_vertex_count;
	}
	Vertex vertex_array_object::vertex(size_t index) const
	{
		auto ppos = index * pointSize();
		auto cpos = index * colorSize();
		return Vertex(
			{ m_points[ppos], m_points[ppos + 1], m_points[ppos + 2] },
			{ m_colors[cpos], m_colors[cpos + 1], m_colors[cpos + 2], m_colors[cpos + 3] }
		);
	}
	void vertex_array_object::vertex(size_t index, const Vertex &vertex)
	{
		auto ppos		   = index * pointSize();
		auto cpos		   = index * colorSize();
		m_points[ppos]	   = vertex.position.x;
		m_points[ppos + 1] = vertex.position.y;
		m_points[ppos + 2] = vertex.position.z;
		m_colors[cpos]	   = vertex.color.r;
		m_colors[cpos + 1] = vertex.color.g;
		m_colors[cpos + 2] = vertex.color.b;
		m_colors[cpos + 3] = vertex.color.a;
	}
	void vertex_array_object::push_back(const Vertex &vertex)
	{
		m_points.push_back(vertex.position.x);
		m_points.push_back(vertex.position.y);
		m_points.push_back(vertex.position.z);
		m_colors.push_back(vertex.color.r);
		m_colors.push_back(vertex.color.g);
		m_colors.push_back(vertex.color.b);
		m_colors.push_back(vertex.color.a);
		m_vertex_count++;
	}
	void vertex_array_object::insert(size_t index, const Vertex &vertex)
	{
		auto ppos = m_points.begin() + index * pointSize();
		auto cpos = m_colors.begin() + index * colorSize();
		m_points.insert(ppos, vertex.position.z);
		m_points.insert(ppos, vertex.position.y);
		m_points.insert(ppos, vertex.position.x);
		m_colors.insert(ppos, vertex.color.a);
		m_colors.insert(cpos, vertex.color.b);
		m_colors.insert(cpos, vertex.color.g);
		m_colors.insert(cpos, vertex.color.r);
		m_vertex_count++;
	}
	size_t vertex_array_object::lenPoints() const noexcept
	{
		return m_points.size();
	}
	size_t vertex_array_object::lenColors() const noexcept
	{
		return m_colors.size();
	}
	size_t vertex_array_object::valueTypeSize() noexcept
	{
		return sizeof(value_type);
	}
	const float *vertex_array_object::dataPoints() const noexcept
	{
		return m_points.data();
	}
	const float *vertex_array_object::dataColors() const noexcept
	{
		return m_colors.data();
	}
	void vertex_array_object::erase(size_t index)
	{
		auto ppos = m_points.begin() + index * pointSize();
		auto cpos = m_colors.begin() + index * colorSize();
		m_points.erase(ppos, ppos + 3);
		m_colors.erase(cpos, cpos + 4);
		m_vertex_count--;
	}

	void vertex_array_object::unbind() const
	{
		glBindVertexArray(0);
	}
} // namespace sgl
