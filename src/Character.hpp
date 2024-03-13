#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "CubePosition.hpp"
#include "Movement.hpp"
#include "Pyramid.hpp"

#include "SFML/System/Vector2.hpp"

class Character {
  public:
    Character(pyramid::CubePosition cubePos = {}) : mCubePos{cubePos} {}
    virtual ~Character() {}

    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual pyramid::Movement getMovement() = 0;
    virtual void setSpritePosition(const sf::Vector2f& spritePos) = 0;
    virtual pyramid::CubeAction getCubeAction() = 0;

    pyramid::CubePosition mCubePos{};
};

#endif // CHARACTER_HPP
