#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"
#include "CubePosition.hpp"
#include "GameLoopTimer.hpp"
#include "KeyHandler.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"

#include <atomic>
#include <functional>
#include <mutex>

class Player : public Character {
  public:
    Player(Character::IdType id, KeyHandler& keyHandler, GameLoopTimer& gameLoopTimer,
           std::atomic_bool& isPlayerAlive, pyramid::CubePosition cubePos = {})
        : mKeyHandler{keyHandler}, mGameLoopTimer{gameLoopTimer},
          mIsPlayerAlive{isPlayerAlive}, Character{id, cubePos} {
        keyHandler.registerCallback(
            std::bind(&Player::keyHandlerCallback, this, std::placeholders::_1));

        constexpr float kRadius{20.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Green);
    }

    void draw(sf::RenderWindow& window) const override { window.draw(mSprite); }

    pyramid::Movement getMovement() const override {
        std::lock_guard lock{mMovementMutex};
        switch (mMovement) {
        case Movement::kNone:
            return pyramid::Movement::kNone;
        case Movement::kLeft:
            return pyramid::Movement::kUpLeft;
        case Movement::kRight:
            return pyramid::Movement::kDownRight;
        case Movement::kUp:
            return pyramid::Movement::kUpRight;
        case Movement::kDown:
            return pyramid::Movement::kDownLeft;
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

    void keyHandlerCallback(Movement movement) {
        std::lock_guard lock{mMovementMutex};
        switch (movement) {
        case Movement::kNone:
            break;
        case Movement::kLeft:
        case Movement::kRight:
        case Movement::kUp:
        case Movement::kDown:
            mMovement = movement;
            break;
        }
    }

    void updateLoopCompleteCallback() override {
        std::lock_guard lock{mMovementMutex};
        mMovement = Movement::kNone;
    }

    void onCharacterRemoved() override { mIsPlayerAlive = false; }

  private:
    sf::CircleShape mSprite;

    KeyHandler& mKeyHandler;
    const GameLoopTimer& mGameLoopTimer;
    std::atomic_bool& mIsPlayerAlive;

    Movement mMovement{Movement::kNone};
    mutable std::mutex mMovementMutex;
};

#endif // PLAYER_HPP
