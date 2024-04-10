#ifndef COILY_ENEMY_HPP
#define COILY_ENEMY_HPP

#include "Character.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

class CoilyEnemy : public Character {
  public:
    CoilyEnemy(Character::IdType id) : Character{id} {
        constexpr float kRadius{20.0F};
        mSprite.setRadius(kRadius);
        mSprite.setOrigin(kRadius, kRadius);
        mSprite.setFillColor(sf::Color::Magenta);
    }

    void draw(sf::RenderWindow& window) const override { window.draw(mSprite); }

    pyramid::Movement getMovement() const override {
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
};

#endif // COILY_ENEMY_HPP
