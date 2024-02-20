#ifndef CHARACTER_MANAGER_HPP
#define CHARACTER_MANAGER_HPP

#include <memory>
#include <utility>
#include <vector>

#include "BallEnemy.hpp"
#include "CoilyEnemy.hpp"
#include "ICharacter.hpp"
#include "Player.hpp"
#include "Pyramid.hpp"

class CharacterManager {
  public:
    using CharacterList = std::vector<std::shared_ptr<ICharacter>>;

    void update() {
        for (auto& character : mCharacters) {
            // character->mPos = ;
            // character->mSprite.move(pyramid::movementToVector(character->getMovement()));
        }
    }

    template <typename... Args> void createPlayer(Args&&... args) {
        mCharacters.emplace_back(std::make_shared<Player>(std::forward<Args>(args)...));
    }

    template <typename... Args> void createBall(Args&&... args) {
        mCharacters.emplace_back(
            std::make_shared<BallEnemy>(std::forward<Args>(args)...));
    }

    template <typename... Args> void createCoily(Args&&... args) {
        mCharacters.emplace_back(
            std::make_shared<CoilyEnemy>(std::forward<Args>(args)...));
    }

    // private:
    CharacterList mCharacters;
};

#endif // CHARACTER_MANAGER_HPP
