#ifndef COILY_ENEMY_HPP
#define COILY_ENEMY_HPP

#include "ICharacter.hpp"
#include "Movement.hpp"

class CoilyEnemy : public ICharacter {
  public:
    CoilyEnemy() {
        mSprite.setFillColor({255U, 0U, 255U});
        mSprite.setRadius(20U);
    }

    Movement getMovement() override {
        static Movement movement{Movement::kDownLeft};

        switch (movement) {
        case Movement::kUpLeft:
            movement = Movement::kUpRight;

        case Movement::kUpRight:
            movement = Movement::kDownLeft;

        case Movement::kDownLeft:
            movement = Movement::kDownRight;

        case Movement::kDownRight:
            movement = Movement::kUpLeft;
        }

        return movement;
    }
};

#endif // COILY_ENEMY_HPP
