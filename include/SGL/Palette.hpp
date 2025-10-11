#pragma once


#include <vector>
#include "SGL/Color.hpp"


namespace sgl
{
	class Palette : public std::vector<Color>
	{
	public:
		using std::vector<Color>::vector;
		/**
		 * @brief calculates size in bytes
		 *
		 * @return size_t
		 */
		size_t length() const noexcept
		{
			return sizeof(Palette::value_type::value_type) * size();
		}
		/**
		 * @brief simplify the colors of palette (reduces the alpha channel)
		 *
		 * @return std::vector<Color::value_type>
		 */
		std::vector<Color::value_type> toArray3() const
		{
			std::vector<Color::value_type> matrix;
			for (auto &color: *this)
			{
				matrix.push_back(color.r);
				matrix.push_back(color.g);
				matrix.push_back(color.b);
			}
			return matrix;
		}
		/**
		 * @brief one-dimension array
		 *
		 * @return std::vector<Color::value_type>
		 */
		std::vector<Color::value_type> toArray4() const
		{
			std::vector<Color::value_type> matrix;
			for (auto &color: *this)
			{
				matrix.push_back(color.r);
				matrix.push_back(color.g);
				matrix.push_back(color.b);
				matrix.push_back(color.a);
			}
			return matrix;
		}
		const Color *ptr() const noexcept
		{
			if (empty())
				return nullptr;
			return &at(0);
		}
	};
} // namespace sgl
