#ifndef BALL_ENEMY_HPP
#define BALL_ENEMY_HPP

#include "ICharacter.hpp"
#include "Movement.hpp"

class BallEnemy : public ICharacter {
  public:
    BallEnemy() {
        mSprite.setFillColor({255U, 0U, 0U});
        mSprite.setRadius(10U);
    }

    Movement getMovement() override {
        static bool toggle{false};
        toggle = !toggle;

        return (toggle ? Movement::kDownLeft : Movement::kDownRight);
    }
};

#endif // BALL_ENEMY_HPP
