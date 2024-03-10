#ifndef MATH_UTILS_HPP
#define MATH_UTILS_HPP

#include <SFML/System/Vector2.hpp>

inline sf::Vector2f scalarMult(float scalar, const sf::Vector2f& vector) {
    return {scalar * vector.x, scalar * vector.y};
}

#endif // MATH_UTILS_HPP
