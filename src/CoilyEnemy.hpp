#ifndef COILY_ENEMY_HPP
#define COILY_ENEMY_HPP

#include "ICharacter.hpp"
#include "Movement.hpp"

#include <SFML/Graphics/Color.hpp>

class CoilyEnemy : public ICharacter {
  public:
    CoilyEnemy() {
        constexpr float kRadius{20.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Magenta);
    }

    pyramid::Movement getMovement() override {
        static pyramid::Movement movement{pyramid::Movement::kDownLeft};

        switch (movement) {
        case pyramid::Movement::kNone:
            movement = pyramid::Movement::kUpRight;
            break;

        case pyramid::Movement::kUpLeft:
            movement = pyramid::Movement::kUpRight;
            break;

        case pyramid::Movement::kUpRight:
            movement = pyramid::Movement::kDownLeft;
            break;

        case pyramid::Movement::kDownLeft:
            movement = pyramid::Movement::kDownRight;
            break;

        case pyramid::Movement::kDownRight:
            movement = pyramid::Movement::kUpLeft;
            break;
        }

        return movement;
    }
};

#endif // COILY_ENEMY_HPP
