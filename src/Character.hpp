#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Cube.hpp"
#include "CubePosition.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class Character {
  public:
    Character(pyramid::CubePosition cubePos = {}) : mPosition{cubePos} {}
    virtual ~Character() {}

    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual pyramid::Movement getMovement() = 0;
    virtual void setSpritePosition(const sf::Vector2f& spritePos) = 0;
    virtual pyramid::CubeAction getCubeAction() = 0;

    pyramid::CubePosition getPosition() const { return mPosition; }
    pyramid::CubePosition getPreviousPosition() const { return mPreviousPosition; }
    bool isNewPosition() const { return mPosition != mPreviousPosition; }

    void setPosition(const pyramid::CubePosition& cubePosition) {
        mPreviousPosition = mPosition;
        mPosition = cubePosition;
    }

  private:
    pyramid::CubePosition mPosition{};
    pyramid::CubePosition mPreviousPosition{};
};

#endif // CHARACTER_HPP
