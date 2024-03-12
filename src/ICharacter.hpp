#ifndef I_CHARACTER_HPP
#define I_CHARACTER_HPP

#include "CubePosition.hpp"
#include "Movement.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class ICharacter {
  public:
    ICharacter(pyramid::CubePosition pos = {}) : mPos{pos} {}
    virtual ~ICharacter() {}

    pyramid::CubePosition mPos{};
    sf::CircleShape mSprite;

    virtual pyramid::Movement getMovement() = 0;
};

#endif // I_CHARACTER_HPP
