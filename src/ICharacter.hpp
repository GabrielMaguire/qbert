#ifndef I_CHARACTER_HPP
#define I_CHARACTER_HPP

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

#include "Movement.hpp"
#include "Pyramid.hpp"

class ICharacter {
  public:
    ICharacter(pyramid::CubePosition pos = {}) : mPos{pos} {}
    virtual ~ICharacter() {}

    pyramid::CubePosition mPos{};
    sf::CircleShape mSprite;

    virtual Movement getMovement() = 0;
    virtual void die() {
        //
    }
};

#endif // I_CHARACTER_HPP
