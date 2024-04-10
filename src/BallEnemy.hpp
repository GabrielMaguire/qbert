#ifndef BALL_ENEMY_HPP
#define BALL_ENEMY_HPP

#include "Character.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

class BallEnemy : public Character {
  public:
    BallEnemy(Character::IdType id) : Character{id} {
        constexpr float kRadius{10.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow& window) const override { window.draw(mSprite); }

    pyramid::Movement getMovement() const override {
        static bool toggle{false};
        toggle = !toggle;

        return (toggle ? pyramid::Movement::kDownLeft : pyramid::Movement::kDownRight);
    }

    void setSpritePosition(const sf::Vector2f& spritePos) override {
        mSprite.setPosition(spritePos);
    }

    pyramid::CubeAction getCubeAction() const override {
        return pyramid::CubeAction::kNone;
    }

    CharacterInteraction getInteraction() const override {
        return CharacterInteraction::kHostile;
    }

  private:
    sf::CircleShape mSprite;
};

#endif // BALL_ENEMY_HPP
