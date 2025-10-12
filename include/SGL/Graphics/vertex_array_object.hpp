#pragma once

#include "SGL/SGLfwd.hpp"
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "SGL/VertexArray.hpp"

namespace sgl
{
	class vertex_array_object
	{
	public:
		using value_type		 = float;
		using points_vector_type = std::vector<value_type>;
		using colors_vector_type = std::vector<value_type>;
		~vertex_array_object();
		void gen() const;
		void assign(const VertexArray &);
		void assign(const std::vector<Point> &, Color general_color = Color::white);
		void del() const;
		void bind() const;
		void unbind() const;
		void push_back(const Vertex &vertex);
		void insert(size_t index, const Vertex &vertex);
		size_t getVertexCount() const noexcept;
		/**
		 * @brief value count of points {[0]p1.x, [1]p1.y, [2]p1.z, [3]p2.x, ...} - count
		 *
		 * @param callback
		 * @return size_t
		 */
		size_t lenPoints() const noexcept;
		/**
		 * @brief value count of colors {[0]p1.r, [1]p1.g, [2]p1.b, [3]p1.a, [4]p2.r, ...} - count
		 *
		 * @param callback
		 * @return size_t
		 */
		size_t lenColors() const noexcept;
		/**
		 * @brief getting the point dimentions count
		 *
		 * @return size_t
		 */
		constexpr static size_t pointSize()
		{
			return 3;
		}
		/**
		 * @brief getting the color channels count
		 *
		 * @return size_t
		 */
		constexpr static size_t colorSize()
		{
			return 4;
		}
		static size_t valueTypeSize() noexcept;
		void transformPoints(const std::function<Point(const Point &)> &transformation_func);
		void setVertexColor(size_t vertex, Color color);
		const float *dataPoints() const noexcept;
		const float *dataColors() const noexcept;
		void erase(size_t index);
		Vertex vertex(size_t index) const;
		void vertex(size_t index, const Vertex &vertex);

	private:
		mutable GLuint m_vertex_array = 0;
		points_vector_type m_points{};
		colors_vector_type m_colors{};
		size_t m_vertex_count = 0;
	};
} // namespace sgl
