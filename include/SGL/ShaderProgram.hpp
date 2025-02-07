#pragma once

#include <vector>
#include "SGLdecl.hpp"

#include "ShaderData.hpp"
#include "VertexArray.hpp"


namespace sgl
{
	class ShaderProgram : public std::vector<ShaderData>
	{
	public:
		enum PrimitiveType 
		{
			Triangles,
			TriangleStrip,
			TriangleFan,
			Points,
			Lines,
			LineStrip,
			LineLoop,
			Quads,
			Unknown,
		};
	private:
		// vertices use two descriptors: [0] point, [1] color
		GLuint vbos[2] = {0, 0};
		GLuint vertex_array = 0;
		GLuint program		   = glCreateProgram();
		VertexArray vertices;
		PrimitiveType draw_algorithm = TriangleFan;
		static GLenum toDrawAlgorithm(PrimitiveType draw_algorithm);

	public:
		ShaderProgram() {}
		ShaderProgram(const ShaderProgram &)			= delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;
		~ShaderProgram();
		void bindBuffers();
		void build();
		void attach() const;
		void render() const;
		void link() const;
		void setVertexCount(size_t count);
		PrimitiveType getPrimitiveType() const;
		void setPrimitiveType(PrimitiveType);
		template<class Iter>
		void assignVertices(Iter begin, const Iter &end);
		Vertex &getVertex(size_t i);
		const Vertex &getVertex(size_t i) const;
	};

	template<class Iter>
	void ShaderProgram::assignVertices(Iter begin, const Iter &end)
	{
		vertices.assign(begin, end);
	}
} // namespace sgl
