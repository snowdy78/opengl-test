#pragma once

#include <vector>
#include "Graphics/vertex_array_object.hpp"
#include "ShaderData.hpp"

namespace sgl
{
	class ShaderProgram
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
		GLuint program{ glCreateProgram() };
		PrimitiveType draw_algorithm{ TriangleFan };
		mutable vertex_array_object m_vao{};
		mutable bool need_build{ true };
		mutable std::vector<ShaderData> m_shaders;
		friend void ShaderData::attach(const ShaderProgram &program) const;

	private:
		void makeBuild() const;

	public:
		ShaderProgram();
		ShaderProgram(const ShaderProgram &)			= delete;
		ShaderProgram &operator=(const ShaderProgram &) = delete;
		~ShaderProgram();
		void updateBuffers() const;
		void build() const;
		void render() const;
		void link() const;
		size_t getVertexCount() const;
		PrimitiveType getPrimitiveType() const;
		void setPrimitiveType(PrimitiveType);
		void assignVertices(const VertexArray &vertex_array);
		Vertex getVertex(size_t i) const;
		void setVertex(size_t i, const Vertex &v);
		void addVertex(const Vertex &vertex);
		void insertVertex(size_t index, const Vertex &vertex);
		void emplace_back(ShaderData::Type type);
		void transformPoints(std::function<glm::vec3(const glm::vec3 &)> transformation_func);
		void push_back(ShaderData &&shader_data);
		size_t size() const;
		void clear();
	};

} // namespace sgl
