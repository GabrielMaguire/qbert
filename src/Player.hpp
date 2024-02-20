#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ICharacter.hpp"
#include "Movement.hpp"
#include "Pyramid.hpp"

class Player : public ICharacter {
  public:
    Player(pyramid::CubePosition pos = {}) : ICharacter{pos} {
        mSprite.setFillColor({0U, 255U, 0U});
        mSprite.setRadius(20U);
    }

    Movement getMovement() override { return Movement::kDownRight; }
};

#endif // PLAYER_HPP
