#include "CharacterManager.hpp"

#include "Character.hpp"
#include "CubePosition.hpp"
#include "Player.hpp"
#include "Pyramid.hpp"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

void CharacterManager::initialize() {
    for (auto& [id, character] : mCharacters) {
        character->setSpritePosition(
            mPyramid.characterPositionToVector(character->getPosition()));
    }
}

void CharacterManager::update() {
    using CollisionList = std::vector<std::shared_ptr<Character>>;
    using CollisionMap = std::unordered_map<pyramid::CubePosition, CollisionList>;

    CollisionMap collisionMap;
    std::vector<Character::IdType> outOfBoundsCharacterIds{};
    std::vector<Character::IdType> hostileCollisionCharacterIds{};

    for (auto& [id, character] : mCharacters) {
        pyramid::CubePosition updatedPosition{mPyramid.getUpdatedPosition(
            character->getPosition(), character->getMovement())};
        character->setPosition(updatedPosition);

        if (!mPyramid.isPositionInBounds(updatedPosition)) {
            outOfBoundsCharacterIds.emplace_back(id);
            continue;
        }

        character->setSpritePosition(mPyramid.characterPositionToVector(updatedPosition));

        if (auto itr{collisionMap.find(updatedPosition)}; itr != collisionMap.end()) {
            // Add character to existing collision list
            auto& [position, collisionList]{*itr};
            collisionList.emplace_back(character);
        } else {
            // Create new collision list and add to collision map
            collisionMap.emplace(std::make_pair(updatedPosition, std::vector{character}));
        }

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
    }

    for (auto& [position, collisionList] : collisionMap) {
        bool hostileCharacterPresent{false};
        for (auto& character : collisionList) {
            if (character->getInteraction() == CharacterInteraction::kHostile) {
                hostileCharacterPresent = true;
                break;
            }
        }

        if (hostileCharacterPresent && collisionList.size() > 1U) {
            for (auto& character : collisionList) {
                if (character->getInteraction() == CharacterInteraction::kVulnerable) {
                    hostileCollisionCharacterIds.emplace_back(character->getId());
                }
            }
        }
    }

    for (const Character::IdType id : outOfBoundsCharacterIds) {
        mCharacters.erase(id);
    }

    for (const Character::IdType id : hostileCollisionCharacterIds) {
        mCharacters.erase(id);
    }

    for (auto& [id, character] : mCharacters) {
        character->updateLoopCompleteCallback();
    }
}

void CharacterManager::draw(sf::RenderWindow& window) {
    for (auto& [id, character] : mCharacters) {
        character->draw(window);
    }
}
