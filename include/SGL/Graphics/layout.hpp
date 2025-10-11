#pragma once

#include "SGL/SGLfwd.hpp"

namespace sgl
{
	struct layout
	{
		enum GLType
		{
			Float					  = GL_FLOAT,
			Int						  = GL_INT,
			UnsignedInt				  = GL_UNSIGNED_INT,
			Byte					  = GL_BYTE,
			UnsignedByte			  = GL_UNSIGNED_BYTE,
			Short					  = GL_SHORT,
			UnsignedShort			  = GL_UNSIGNED_SHORT,
			Double					  = GL_DOUBLE,
			HalfFloat				  = GL_HALF_FLOAT,
			Fixed					  = GL_FIXED,
			Int2_10_10_10Rev		  = GL_INT_2_10_10_10_REV,
			UnsignedInt2_10_10_10Rev  = GL_UNSIGNED_INT_2_10_10_10_REV,
			UnsignedInt10f_11f_11fRev = GL_UNSIGNED_INT_10F_11F_11F_REV,
			Unknown					  = -1,
		};
		size_t m_location;
		size_t m_size;
		GLType m_type;
		bool m_normalized;
		size_t m_stride;
		void *m_pointer{ nullptr };

	public:
		layout(
			size_t location, size_t size, GLType type = Float, bool normalized = false, size_t stride = 0,
			void *pointer = nullptr
		)
			: m_location(location),
			  m_size(size),
			  m_type(type),
			  m_normalized(normalized),
			  m_stride(stride),
			  m_pointer(pointer)
		{}
		size_t location() const
		{
			return m_location;
		}
		size_t size() const
		{
			return m_size;
		}
		GLType type() const
		{
			return m_type;
		}
		template<class T>
		constexpr GLType is() const
		{
			if (std::is_same<T, float>::value)
				return Float;
			else if (std::is_same<T, int>::value)
				return Int;
			else if (std::is_same<T, unsigned int>::value)
				return UnsignedInt;
			else if (std::is_same<T, double>::value)
				return Double;
			else if (std::is_same<T, short>::value)
				return Short;
			else if (std::is_same<T, unsigned short>::value)
				return UnsignedShort;
			else if (std::is_same<T, char>::value)
				return Byte;
			else if (std::is_same<T, unsigned char>::value)
				return UnsignedByte;
			else
				return Unknown;
		}
		bool normalized() const
		{
			return m_normalized;
		}
		size_t stride() const
		{
			return m_stride;
		}
		void *pointer() const
		{
			return m_pointer;
		}
	};
} // namespace sgl
