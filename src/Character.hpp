#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Cube.hpp"
#include "CubePosition.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

enum class CharacterInteraction { kHostile, kNeutral, kVulnerable };

class Character {
  public:
    using IdType = std::uint16_t;

    Character(IdType id, pyramid::CubePosition cubePos = {})
        : mId{id}, mPosition{cubePos}, mPreviousPosition{cubePos} {}
    virtual ~Character() {}

    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual pyramid::Movement getMovement() const = 0;
    virtual void setSpritePosition(const sf::Vector2f& spritePos) = 0;
    virtual pyramid::CubeAction getCubeAction() const = 0;
    virtual CharacterInteraction getInteraction() const = 0;

    IdType getId() const { return mId; }
    pyramid::CubePosition getPosition() const { return mPosition; }
    pyramid::CubePosition getPreviousPosition() const { return mPreviousPosition; }
    bool isNewPosition() const { return mPosition != mPreviousPosition; }

    virtual void setPosition(const pyramid::CubePosition& cubePosition) {
        mPreviousPosition = mPosition;
        mPosition = cubePosition;
    }

  private:
    const IdType mId;
    pyramid::CubePosition mPosition{};
    pyramid::CubePosition mPreviousPosition{};
};

#endif // CHARACTER_HPP
