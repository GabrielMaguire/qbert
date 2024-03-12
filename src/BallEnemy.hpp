#ifndef BALL_ENEMY_HPP
#define BALL_ENEMY_HPP

#include "ICharacter.hpp"
#include "Movement.hpp"

#include <SFML/Graphics/Color.hpp>

class BallEnemy : public ICharacter {
  public:
    BallEnemy() {
        constexpr float kRadius{10.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Red);
    }

    pyramid::Movement getMovement() override {
        static bool toggle{false};
        toggle = !toggle;

        return (toggle ? pyramid::Movement::kDownLeft : pyramid::Movement::kDownRight);
    }
};

#endif // BALL_ENEMY_HPP
