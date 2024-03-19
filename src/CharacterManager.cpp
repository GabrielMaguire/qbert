#include "CharacterManager.hpp"

#include "CubePosition.hpp"
#include "Pyramid.hpp"

#include <vector>

void CharacterManager::initialize() {
    for (auto& [id, character] : mCharacters) {
        character->setSpritePosition(
            mPyramid.characterPositionToVector(character->getPosition()));
    }
}

void CharacterManager::update() {
    std::vector<IdType> outOfBoundsCharacters{};

    for (auto& [id, character] : mCharacters) {
        pyramid::CubePosition updatedPosition{mPyramid.getUpdatedPosition(
            character->getPosition(), character->getMovement())};
        character->setPosition(updatedPosition);

        if (mPyramid.isPositionInBounds(updatedPosition)) {
            character->setSpritePosition(
                mPyramid.characterPositionToVector(updatedPosition));

            if (character->isNewPosition()) {
                switch (character->getCubeAction()) {
                case pyramid::CubeAction::kNone:
                    break;

                case pyramid::CubeAction::kActivate:
                    mPyramid.activate(updatedPosition);
                    break;

                case pyramid::CubeAction::kDeactivate:
                    mPyramid.deactivate(updatedPosition);
                    break;
                }
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
