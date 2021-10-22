#ifndef _Util_HPP
#define _Util_HPP

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <types.hpp>

namespace util {
static sf::Vector2f CenterOfBounds(const auto& bounds)
{
	return sf::Vector2f(static_cast<f32>(bounds.x) / 2, static_cast<f32>(bounds.y) / 2);
}

static sf::Vector2f CenterOfBounds(const auto& bounds, const auto& size)
{
	return sf::Vector2f((static_cast<f32>(bounds.x) / 2) - static_cast<f32>(size.x),
	                    (static_cast<f32>(bounds.y) / 2) - static_cast<f32>(size.y));
}

static constexpr u32 RGBAToInt(u8 r, u8 g, u8 b, u8 a = 0xff)
{
	return static_cast<u32>(((static_cast<u32>(r)) << 24) | (((static_cast<u32>(g)) & 0xFF) << 16)
	                        | (((static_cast<u32>(b)) & 0xFF) << 8) | ((static_cast<u32>(a)) & 0xFF));
}

static constexpr auto WrapValue(auto value, auto max, auto min)
{
	while (value < min) {
		value += min - value;
	}

	while (value > max) {
		value -= max;
	}

	return value;
}
} // namespace util

#endif