#include "SGL/Graphics/buffer.hpp"

namespace sgl
{
	buffer::buffer(target_type target, usage_type type)
		: m_target_type(target),
		  m_usage_type(type),
		  m_item_length(0)
	{}
	buffer::buffer(buffer &&other) noexcept
		: m_target_type(other.m_target_type),
		  m_usage_type(other.m_usage_type),
		  m_item_length(other.m_item_length),
		  m_buffer(std::move(other.m_buffer))
	{
		other.m_item_length = 0;
		other.m_target_type = target_type::UnknownTarget;
		other.m_usage_type	= usage_type::UnknownUsage;
	}
	size_t buffer::length() const noexcept
	{
		return m_item_length * m_buffer.size();
	}
	const void *buffer::data() const
	{
		return *m_buffer.data();
	}
	buffer::target_type buffer::getTargetType() const noexcept
	{
		return m_target_type;
	}
	buffer::usage_type buffer::getUsageType() const noexcept
	{
		return m_usage_type;
	}
	buffer &buffer::operator=(buffer &&other) noexcept
	{
		if (this != &other)
		{
			m_target_type		= other.m_target_type;
			other.m_target_type = UnknownTarget;
			m_usage_type		= other.m_usage_type;
			other.m_usage_type	= UnknownUsage;
			m_item_length		= other.m_item_length;
			m_buffer			= std::move(other.m_buffer);
		}
		return *this;
	}
	size_t buffer::size() const noexcept
	{
		return m_buffer.size();
	}
} // namespace sgl
