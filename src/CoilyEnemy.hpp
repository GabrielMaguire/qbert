#ifndef COILY_ENEMY_HPP
#define COILY_ENEMY_HPP

#include "Character.hpp"
#include "CharacterUtils.hpp"
#include "KeyHandler.hpp"
#include "Movement.hpp"
#include "Pyramid.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

#include <atomic>

class CoilyEnemy : public Character {
  public:
    CoilyEnemy(Character::IdType id, const pyramid::Pyramid& map,
               std::atomic_bool& isCoilyAlive)
        : Character{id}, mMap{map}, mIsCoilyAlive{isCoilyAlive} {
        constexpr float kRadius{20.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Magenta);

        mIsCoilyAlive = true;
    }

    void draw(sf::RenderWindow& window) const override { window.draw(mSprite); }

    pyramid::Movement getMovement() const override { return mMovement; }

    void setSpritePosition(const sf::Vector2f& spritePos) override {
        mSprite.setPosition(spritePos);
    }

    pyramid::CubeAction getCubeAction() const override {
        return pyramid::CubeAction::kNone;
    }

    CharacterInteraction getInteraction() const override {
        return CharacterInteraction::kHostile;
    }

    void beginUpdateLoop() override {
        switch (mState) {
        case State::kBall: {
            pyramid::Movement movement = getRandomDownwardMovement();
            if (!mMap.isPositionInBounds(
                    mMap.getUpdatedPosition(getPosition(), movement))) {
                movement = pyramid::Movement::kNone;
                mState = State::kCoily;
            }
            mMovement = movement;
        } break;
        case State::kCoily:
            mMovement = getRandomUpwardMovement();
            break;
        }
    }

    void onCharacterRemoved() override { mIsCoilyAlive = false; }

  private:
    enum class State { kBall, kCoily };

    State mState{State::kBall};
    pyramid::Movement mMovement{pyramid::Movement::kNone};
    sf::CircleShape mSprite;
    const pyramid::Pyramid& mMap;
    std::atomic_bool& mIsCoilyAlive;
};

#endif // COILY_ENEMY_HPP
