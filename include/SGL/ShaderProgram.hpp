#pragma once

#include <vector>
#include "SGL/Transform.hpp"
#include "SGL\SGLfwd.hpp"

#include "ShaderData.hpp"
#include "VertexArray.hpp"


namespace sgl
{
	class ShaderProgram : public std::vector<ShaderData>
	{
	public:
		enum PrimitiveType
		{
			Triangles			   = GL_TRIANGLES,
			TriangleStrip		   = GL_TRIANGLE_STRIP,
			TriangleFan			   = GL_TRIANGLE_FAN,
			Points				   = GL_POINTS,
			Lines				   = GL_LINES,
			LineStrip			   = GL_LINE_STRIP,
			LineLoop			   = GL_LINE_LOOP,
			LineStripAdjacency	   = GL_LINE_STRIP_ADJACENCY,
			LinesAdjacency		   = GL_LINES_ADJACENCY,
			TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
			TrianglesAdjacency	   = GL_TRIANGLES_ADJACENCY,
			Patches				   = GL_PATCHES,
			Unknown				   = -1,
		};

	private:
		// vertices use two descriptors: [0] point, [1] color
		mutable std::vector<GLuint> vertex_buffers;
		mutable GLuint vertex_array = 0;
		mutable GLuint program		= glCreateProgram();
		VertexArray vertices;
		PrimitiveType draw_algorithm = TriangleFan;
		mutable bool need_build		 = true;
		void makeBuild() const;

	public:
		mutable Transform transform;
		ShaderProgram();
		ShaderProgram(const ShaderProgram &)			= delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;
		~ShaderProgram();
		void bindBuffers() const;
		void build() const;
		void attach() const;
		void render() const;
		void link() const;
		void setVertexCount(size_t count);
		size_t getVertexCount() const;
		PrimitiveType getPrimitiveType() const;
		void setPrimitiveType(PrimitiveType);
		template<class Iter>
		void assignVertices(Iter begin, const Iter &end);
		const Vertex &getVertex(size_t i) const;
		void setVertex(size_t i, const Vertex &v);

	protected:
		void onTransformUpdate() const;
	};

	template<class Iter>
	void ShaderProgram::assignVertices(Iter begin, const Iter &end)
	{
		vertices.assign(begin, end);
		build();
	}
} // namespace sgl
