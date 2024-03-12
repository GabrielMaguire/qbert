#include "CharacterManager.hpp"

#include "Pyramid.hpp"

#include <vector>

void CharacterManager::initialize() {
    for (auto& [id, character] : mCharacters) {
        character->mSprite.setPosition(
            mPyramid.characterPositionToVector(character->mPos));
    }
}

void CharacterManager::update() {
    std::vector<IdType> outOfBoundsCharacters{};

    for (auto& [id, character] : mCharacters) {
        pyramid::Movement movement{character->getMovement()};
        mPyramid.updatePosition(character->mPos, movement);

        if (mPyramid.isPositionInBounds(character->mPos)) {
            character->mSprite.setPosition(
                mPyramid.characterPositionToVector(character->mPos));
        } else {
            outOfBoundsCharacters.emplace_back(id);
        }
    }

    for (const IdType id : outOfBoundsCharacters) {
        mCharacters.erase(id);
    }
}

void CharacterManager::draw(sf::RenderWindow& window) {
    for (auto& [id, character] : mCharacters) {
        window.draw(character->mSprite);
    }
}
