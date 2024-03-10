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
#include "SFML/System/Vector2.hpp"

class CharacterManager {
  public:
    using CharacterList = std::vector<std::shared_ptr<ICharacter>>;

    CharacterManager(const pyramid::Pyramid& pyramid) : mPyramid{pyramid} {}

    void draw(sf::RenderWindow& window) {
        for (auto& character : mCharacters) {
            window.draw(character->mSprite);
        }
    }

    void initialize() {
        for (auto& character : mCharacters) {
            character->mSprite.setPosition(mPyramid.positionToVector(character->mPos));
        }
    }

    void update() {
        for (auto& character : mCharacters) {
            pyramid::Movement movement{character->getMovement()};
            pyramid::updatePosition(character->mPos, movement);
            character->mSprite.setPosition(mPyramid.positionToVector(character->mPos));
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

  private:
    const pyramid::Pyramid& mPyramid;
    CharacterList mCharacters;
};

#endif // CHARACTER_MANAGER_HPP
