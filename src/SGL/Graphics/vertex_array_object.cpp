#include "SGL/Graphics/vertex_array_object.hpp"

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
		glDeleteVertexArrays(1, &m_vertex_array);
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

	void vertex_array_object::transformPoints(const std::function<glm::vec3(const glm::vec3 &)> &callback)
	{
		for (size_t i = 0; i < m_points.size(); i += 3)
		{
			auto &x = m_points[i], &y = m_points[i + 1], &z = m_points[i + 2];
			auto point = callback({ m_points[i], m_points[i + 1], m_points[i + 2] });
			x		   = point.x;
			y		   = point.y;
			z		   = point.z;
		}
	}
	void vertex_array_object::setVertexColor(size_t vertex, Color color)
	{
		m_colors[vertex * 4 + 0] = color.r;
		m_colors[vertex * 4 + 1] = color.g;
		m_colors[vertex * 4 + 2] = color.b;
		m_colors[vertex * 4 + 3] = color.a;
	}
	size_t vertex_array_object::getVertexCount() const noexcept
	{
		return m_vertex_count;
	}
	Vertex vertex_array_object::vertex(size_t index) const
	{
		return Vertex(
			{ m_points[index * 3], m_points[index * 3 + 1], m_points[index * 3 + 2] },
			{ m_colors[index * 4], m_colors[index * 4 + 1], m_colors[index * 4 + 2], m_colors[index * 4 + 3] }
		);
	}
	void vertex_array_object::vertex(size_t index, const Vertex &vertex)
	{
		m_points[index * 3]		= vertex.position.x;
		m_points[index * 3 + 1] = vertex.position.y;
		m_points[index * 3 + 2] = vertex.position.z;
		m_colors[index * 4]		= vertex.color.r;
		m_colors[index * 4 + 1] = vertex.color.g;
		m_colors[index * 4 + 2] = vertex.color.b;
		m_colors[index * 4 + 3] = vertex.color.a;
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
		m_points.insert(m_points.begin() + index * 3, vertex.position.z);
		m_points.insert(m_points.begin() + index * 3, vertex.position.y);
		m_points.insert(m_points.begin() + index * 3, vertex.position.x);
		m_colors.insert(m_colors.begin() + index * 4, vertex.color.a);
		m_colors.insert(m_colors.begin() + index * 4, vertex.color.b);
		m_colors.insert(m_colors.begin() + index * 4, vertex.color.g);
		m_colors.insert(m_colors.begin() + index * 4, vertex.color.r);
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
		m_points.erase(m_points.begin() + index * 3, m_points.begin() + index * 3 + 3);
		m_colors.erase(m_colors.begin() + index * 4, m_colors.begin() + index * 4 + 4);
		m_vertex_count--;
	}

} // namespace sgl
