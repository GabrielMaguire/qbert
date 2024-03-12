#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "CubePosition.hpp"
#include "ICharacter.hpp"
#include "KeyHandler.hpp"
#include "Movement.hpp"
#include "Pyramid.hpp"

#include <SFML/Graphics/Color.hpp>

class Player : public ICharacter {
  public:
    Player(const KeyHandler& keyHandler, pyramid::CubePosition pos = {})
        : mKeyHandler{keyHandler}, ICharacter{pos} {
        constexpr float kRadius{20.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Green);
    }

    pyramid::Movement getMovement() override {
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

  private:
    const KeyHandler& mKeyHandler;
};

#endif // PLAYER_HPP
