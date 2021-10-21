#ifndef _Util_HPP
#define _Util_HPP

#include <SFML/Graphics.hpp>
#include <type_traits>
#include <types.hpp>

namespace util {
static sf::Vector2f CenterOfBounds(const auto& bounds)
{
	return sf::Vector2f(static_cast<f32>(bounds.x) / 2,
	                    static_cast<f32>(bounds.y) / 2);
}

static sf::Vector2f CenterOfBounds(const auto& bounds, const auto& size)
{
	return sf::Vector2f(
	    (static_cast<f32>(bounds.x) / 2) - static_cast<f32>(size.x),
	    (static_cast<f32>(bounds.y) / 2) - static_cast<f32>(size.y));
}
} // namespace util

#endif