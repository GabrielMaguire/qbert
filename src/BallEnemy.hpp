#ifndef BALL_ENEMY_HPP
#define BALL_ENEMY_HPP

#include "Character.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

#include <random>

class BallEnemy : public Character {
  public:
    BallEnemy(Character::IdType id) : Character{id} {
        constexpr float kRadius{10.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Red);
    }

    void draw(sf::RenderWindow& window) const override { window.draw(mSprite); }

    pyramid::Movement getMovement() const override { return getRandomLeftRight(); }

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

    pyramid::Movement getRandomLeftRight() const {
        static auto gen = std::bind(std::uniform_int_distribution<>(0, 1),
                                    std::default_random_engine());
        return gen() ? pyramid::Movement::kDownLeft : pyramid::Movement::kDownRight;
    }
};

#endif // BALL_ENEMY_HPP
