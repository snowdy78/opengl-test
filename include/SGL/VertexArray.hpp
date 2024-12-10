#pragma once

#include <vector>
#include "PointArray.hpp"
#include "SGL/SGLdecl.hpp"
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
            Palette palette(size());
            for (auto &vertex : *this)
            {
                palette[0] = vertex.color;
            }
            return std::move(palette);
        }
        PointArray getPointArray() const
        {
            PointArray point_array(size());
            for (auto &vertex : *this)
            {
                point_array.push_back(vertex.position);
            }
            return std::move(point_array);
        }
	};

} // namespace sgl
