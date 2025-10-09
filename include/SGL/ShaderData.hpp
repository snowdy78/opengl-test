#pragma once

#include <string>
#include "SGL\SGLfwd.hpp"
#include <fstream>

namespace sgl
{
	struct ShaderData
	{
		enum Type
		{
			Vertex		   = GL_VERTEX_SHADER,
			Fragment	   = GL_FRAGMENT_SHADER,
			Geometry	   = GL_GEOMETRY_SHADER,
			TessEvaluation = GL_TESS_EVALUATION_SHADER,
			TessControl	   = GL_TESS_CONTROL_SHADER,
			Compute		   = GL_COMPUTE_SHADER,
			Unknown		   = -1
		};
		enum BufferAllocationType
		{
			Static	= GL_STATIC_DRAW,
			Dynamic = GL_DYNAMIC_DRAW,
			Stream	= GL_STREAM_DRAW
		};

	private:
		BufferAllocationType buffer_type = Static;
		Type type						 = Unknown;
		GLuint shader					 = 0;

		friend class ShaderProgram;
		void create(const std::string &source_code);

	public:
		ShaderData(Type type);
		~ShaderData();

		bool setCode(const std::string &code);
		ShaderData(const ShaderData &another_shader) = delete;
		ShaderData(ShaderData &&other);
		bool exist() const;
		GLuint getDescriptor() const; // TODO move to private
		BufferAllocationType getBufferAllocType() const;
		void setBufferAllocType(BufferAllocationType type);
		Type getType() const;
		bool compile() const;
		void remove();
	};
	/**
	 * @brief Get the File Data object
	 *
	 * @param path - path to file
	 * @param openmode -
	 * @return std::string
	 */
	std::string getFileData(const std::string &path, std::ios_base::openmode openmode = std::ios_base::in);

} // namespace sgl
