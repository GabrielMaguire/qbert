#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"
#include "CubePosition.hpp"
#include "KeyHandler.hpp"
#include "Movement.hpp"

#include "Pyramid.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"

class Player : public Character {
  public:
    Player(Character::IdType id, const KeyHandler& keyHandler,
           pyramid::CubePosition cubePos = {})
        : mKeyHandler{keyHandler}, Character{id, cubePos} {
        constexpr float kRadius{20.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Green);
    }

    void draw(sf::RenderWindow& window) const override { window.draw(mSprite); }

    pyramid::Movement getMovement() const override {
        switch (mKeyHandler.getMovement()) {
        case Movement::kNone:
            return pyramid::Movement::kNone;
            break;

        case Movement::kLeft:
            return pyramid::Movement::kUpLeft;
            break;

        case Movement::kRight:
            return pyramid::Movement::kDownRight;
            break;

        case Movement::kUp:
            return pyramid::Movement::kUpRight;
            break;

        case Movement::kDown:
            return pyramid::Movement::kDownLeft;
            break;
        }
    }

    void setSpritePosition(const sf::Vector2f& spritePos) override {
        mSprite.setPosition(spritePos);
    }

    pyramid::CubeAction getCubeAction() const override {
        return pyramid::CubeAction::kActivate;
    }

    CharacterInteraction getInteraction() const override {
        return CharacterInteraction::kVulnerable;
    }

  private:
    sf::CircleShape mSprite;
    const KeyHandler& mKeyHandler;
};

#endif // PLAYER_HPP
