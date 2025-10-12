#pragma once

#include <ios>
#include <string>
#include "SGL\SGLfwd.hpp"
#include <vector>
#include <functional>
#include "SGL/Graphics/buffer.hpp"
#include "SGL/Graphics/layout.hpp"

namespace sgl
{
	struct ShaderData
	{
		friend class ShaderProgram;

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

	private:
		Type m_type{ Unknown };
		std::vector<buffer> m_buffers{};
		mutable std::vector<GLuint> m_descriptors_of_buffers{};
		std::vector<layout> m_layouts{};

		bool isBuffersGenerated() const;
		void assignBuffersDescriptors() const;
		void clearBuffersDescriptors() const;
		void enableVertexAttribArray(size_t location) const;
		void disableVertexAttribArray(size_t location) const;
		void attribPointer(size_t layout_index) const;
		void genBuffers() const;
		void deleteBuffers() const;

		void bindBuffer(size_t index) const;
		void unbindBuffer(size_t index) const;
		void bufferData(size_t index) const;
		GLuint m_shader = 0;

	public:
		std::function<void()> prebuild = []() {};

	private:
		void create(const std::string &source_code);

	public:
		ShaderData(Type type);
		~ShaderData();
		bool setCode(const std::string &code);
		ShaderData(const ShaderData &another_shader) = delete;
		ShaderData(ShaderData &&other);
		bool exist() const;
		void erase(size_t index);
		void push(buffer &&buffer, layout &&layout);
		void clear();
		size_t getBufferCount() const noexcept;
		const buffer &getBuffer(size_t index) const;
		Type getType() const;
		void build() const;
		bool compile() const;
		void remove();
		void attach(const ShaderProgram &program) const;
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
