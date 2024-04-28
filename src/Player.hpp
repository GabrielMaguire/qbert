#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Character.hpp"
#include "CubePosition.hpp"
#include "GameLoopTimer.hpp"
#include "KeyHandler.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"

#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>

class Player : public Character {
  public:
    Player(Character::IdType id, KeyHandler& keyHandler, GameLoopTimer& gameLoopTimer,
           pyramid::CubePosition cubePos = {})
        : mKeyHandler{keyHandler}, mGameLoopTimer{gameLoopTimer}, Character{id, cubePos} {
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

  private:
    sf::CircleShape mSprite;

    KeyHandler& mKeyHandler;
    const GameLoopTimer& mGameLoopTimer;

    Movement mMovement{Movement::kNone};
    mutable std::mutex mMovementMutex;
};

#endif // PLAYER_HPP
