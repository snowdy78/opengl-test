#pragma once

#include "SGL/SGLfwd.hpp"
#include <vector>

namespace sgl
{
	struct buffer
	{
		enum target_type
		{
			Array					= GL_ARRAY_BUFFER,
			AtomicCounter			= GL_ATOMIC_COUNTER_BUFFER,
			CopyReadBuffer			= GL_COPY_READ_BUFFER,
			CopyWriteBuffer			= GL_COPY_WRITE_BUFFER,
			DispatchIndirect		= GL_DISPATCH_INDIRECT_BUFFER,
			DrawIndirect			= GL_DRAW_INDIRECT_BUFFER,
			ElementArray			= GL_ELEMENT_ARRAY_BUFFER,
			PixelPack				= GL_PIXEL_PACK_BUFFER,
			PixelUnpack				= GL_PIXEL_UNPACK_BUFFER,
			ShaderStorage			= GL_SHADER_STORAGE_BUFFER,
			Query					= GL_QUERY_BUFFER,
			Texture					= GL_TEXTURE_BUFFER,
			TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
			Uniform					= GL_UNIFORM_BUFFER,
			UnknownTarget			= -1,
		};
		enum usage_type
		{
			StaticDraw	 = GL_STATIC_DRAW,
			DynamicDraw	 = GL_DYNAMIC_DRAW,
			StreamDraw	 = GL_STREAM_DRAW,
			StreamRead	 = GL_STREAM_READ,
			StreamCopy	 = GL_STREAM_COPY,
			StaticRead	 = GL_STATIC_READ,
			StaticCopy	 = GL_STATIC_COPY,
			DynamicRead	 = GL_DYNAMIC_READ,
			DynamicCopy	 = GL_DYNAMIC_COPY,
			UnknownUsage = -1,
		};

	private:
		target_type m_target_type;
		usage_type m_usage_type;
		size_t m_item_length;
		size_t m_size;
		size_t m_length;
		const void *m_data{};

	public:
		/**
		 * @brief
		 *
		 * @param data - buffer data
		 * @param length - byte length of data
		 * @param count - number of values
		 */
		template<class T>
		buffer(target_type target, usage_type usage, const T *data, size_t count = 1);
		/**
		 * @brief Construct a new buffer object
		 *
		 * @param type
		 */
		buffer(target_type target, usage_type type);
		buffer(const buffer &) = delete;
		buffer(buffer &&other) noexcept;
		/**
		 * @brief initializing a buffer
		 *
		 * @param data - data pointer
		 * @param count - count of data
		 * @tparam T - data item type
		 */
		template<class T>
		void assign(const T *data, size_t count = 1);
		/**
		 * @brief calculates buffer byte length
		 *
		 * @return size_t
		 */
		size_t length() const noexcept;
		size_t size() const noexcept;
		const void *data() const;
		target_type getTargetType() const noexcept;
		usage_type getUsageType() const noexcept;
		buffer &operator=(const buffer &other) = delete;
		buffer &operator=(buffer &&other) noexcept;
	};
	template<class T>
	void buffer::assign(const T *data, size_t count)
	{
		m_item_length = sizeof(T);
		m_size		  = count;
		m_data		  = static_cast<const void *>(data);
		m_length	  = count * m_item_length;
	}

	template<class T>
	buffer::buffer(target_type target, usage_type usage, const T *data, size_t count)
		: m_target_type(target),
		  m_usage_type(usage),
		  m_item_length(sizeof(T))
	{
		assign(data, count);
	}

} // namespace sgl
