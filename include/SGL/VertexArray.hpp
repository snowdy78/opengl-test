#pragma once

#include <vector>
#include "PointArray.hpp"
#include "Vertex.hpp"
#include "Palette.hpp"

namespace sgl
{
	class VertexArray : public std::vector<Vertex>
	{
	public:
		using std::vector<Vertex>::vector;

		Palette getPalette() const
		{
			Palette palette;
			for (auto &vertex: *this)
			{
				palette.push_back(vertex.color);
			}
			return std::move(palette);
		}
		PointArray getPointArray() const
		{
			PointArray points;
			for (auto &vertex: *this)
			{
				points.push_back(vertex.position);
			}
			return std::move(points);
		}
	};

} // namespace sgl
