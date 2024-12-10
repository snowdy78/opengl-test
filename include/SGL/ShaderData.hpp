#pragma once

#include <map>
#include <string>
#include "SGL/ShaderData.hpp"
#include "SGLdecl.hpp"


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
			Compute		   = GL_TESS_CONTROL_SHADER
		};

		class LayoutValue
		{
		protected:
			const void *value;

		public:
			LayoutValue(const void *v)
				: value(v)
			{}
			LayoutValue(nullptr_t v)
				: value(v)
			{}
			LayoutValue &operator=(const void *v)
			{
				value = v;
				return *this;
			}
			LayoutValue &operator=(nullptr_t value)
			{
				this->value = value;
				return *this;
			}
			virtual size_t getSizeInBytes() = 0;
		};

	private:
		using layout_value_type = LayoutValue;
		using layout_t			= std::vector<layout_value_type *>;

	public:
		class ShaderLayout : public layout_t
		{
		public:
			using reference = layout_value_type &;
			using pointer = layout_value_type *;
			using const_reference = const layout_value_type &;
			using const_pointer = const layout_value_type *;
			enum BufferType
			{
				Static	= GL_STATIC_DRAW,
				Dynamic = GL_DYNAMIC_DRAW
			};

		public:
			BufferType buf_type;
			using value_type = layout_value_type;
			using layout_t::layout_t;
			void setBufferType(BufferType type)
			{
				buf_type = type;
			}
			BufferType getBufferType() const
			{
				return buf_type;
			}
			const_pointer ptr() const
			{
				return at(0);
			}
		};

		using layout_array = std::vector<ShaderLayout>;

	private:
		friend class ShaderProgram;

		Type type;
		bool is_created = false;
		GLuint id;
		layout_array layouts;

		GLuint getGLId() const;

		std::string loadFromFile(const std::string &path);
		void create(const std::string &source_code);

	public:
		ShaderData();
		ShaderData(Type type, const std::string &shader_code);
		~ShaderData();

		bool load(const std::string &path, Type type);

		ShaderData(const ShaderData &)			  = delete;
		ShaderData &operator=(const ShaderData &) = delete;

		void setLayoutCount(size_t count);
		void addLayout(size_t index, ShaderLayout::reference layout_value);
		void insertIntoLayout(size_t index, ShaderLayout::reference layout_value);
		void setLayoutValue(size_t layout_id, size_t value_id, const void *layout_value);
		void removeLayout(size_t index);
		const ShaderLayout &layout(size_t index) const;
		size_t getLayoutCount() const;

		Type getType() const;
		bool compile();
		void remove();
	};
} // namespace sgl
