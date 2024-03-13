#include "CharacterManager.hpp"

#include "Pyramid.hpp"

#include <vector>

void CharacterManager::initialize() {
    for (auto& [id, character] : mCharacters) {
        character->setSpritePosition(
            mPyramid.characterPositionToVector(character->mCubePos));
    }
}

void CharacterManager::update() {
    std::vector<IdType> outOfBoundsCharacters{};

    for (auto& [id, character] : mCharacters) {
        mPyramid.updatePosition(character->mCubePos, character->getMovement());

        if (mPyramid.isPositionInBounds(character->mCubePos)) {
            character->setSpritePosition(
                mPyramid.characterPositionToVector(character->mCubePos));

            switch (character->getCubeAction()) {
            case pyramid::CubeAction::kNone:
                break;

            case pyramid::CubeAction::kActivate:
                mPyramid.activate(character->mCubePos);
                break;

            case pyramid::CubeAction::kDeactivate:
                mPyramid.deactivate(character->mCubePos);
                break;
            }
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
        character->draw(window);
    }
}
