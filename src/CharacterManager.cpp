#include "CharacterManager.hpp"

#include "Character.hpp"
#include "CubePosition.hpp"
#include "Pyramid.hpp"

#include <algorithm>
#include <iterator>
#include <memory>
#include <set>
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
    CollisionMap collisionMap{};
    std::set<Character::IdType> outOfBoundsCharacterIds{};

    for (auto& [id, character] : mCharacters) {
        character->beginUpdateLoop();

        pyramid::CubePosition updatedPosition{mPyramid.getUpdatedPosition(
            character->getPosition(), character->getMovement())};
        character->setPosition(updatedPosition);

        if (!mPyramid.isPositionInBounds(updatedPosition)) {
            outOfBoundsCharacterIds.emplace(id);
            continue;
        }

        character->setSpritePosition(mPyramid.characterPositionToVector(updatedPosition));

        addCharacterToCollisionMap(collisionMap, character);

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

    std::set<Character::IdType> hostileCollisionCharacterIds =
        getHostileCharacterCollisions(collisionMap);

    std::set<Character::IdType> charactersToRemove;
    std::set_union(outOfBoundsCharacterIds.begin(), outOfBoundsCharacterIds.end(),
                   hostileCollisionCharacterIds.begin(),
                   hostileCollisionCharacterIds.end(),
                   std::inserter(charactersToRemove, charactersToRemove.begin()));
    for (const Character::IdType id : charactersToRemove) {
        mCharacters.at(id)->onCharacterRemoved();
        mCharacters.erase(id);
    }

    for (auto& [id, character] : mCharacters) {
        character->endUpdateLoop();
    }
}

void CharacterManager::addCharacterToCollisionMap(
    CollisionMap& collisionMap, const std::shared_ptr<Character>& character) const {
    const pyramid::CubePosition position{character->getPosition()};
    const bool isHostile = character->getInteraction() == CharacterInteraction::kHostile;

    if (const auto itr{collisionMap.find(position)}; itr != collisionMap.end()) {
        // Add character to existing collision list
        auto& [collisionPosition, positionInfo]{*itr};
        positionInfo.hostilePresent = positionInfo.hostilePresent || isHostile;
        positionInfo.collisionList.emplace_back(character);
    } else {
        // Create new collision list and add to collision map
        collisionMap.emplace(
            std::make_pair(position, PositionInfo{isHostile, std::vector{character}}));
    }
}

std::set<Character::IdType>
CharacterManager::getHostileCharacterCollisions(const CollisionMap& collisionMap) const {
    auto isSwapWithHostile = [](const std::shared_ptr<Character>& characterUnderTest,
                                const CollisionMap& collisionMap) -> bool {
        if (const auto itr{collisionMap.find(characterUnderTest->getPreviousPosition())};
            itr != collisionMap.cend()) {
            for (const auto& potentialCollisionCharacter : itr->second.collisionList) {
                if (potentialCollisionCharacter->getPreviousPosition() ==
                        characterUnderTest->getPosition() &&
                    potentialCollisionCharacter->getInteraction() ==
                        CharacterInteraction::kHostile) {
                    return true;
                }
            }
        }
        return false;
    };

    std::set<Character::IdType> hostileCollisionCharacterIds{};

    for (const auto& [position, info] : collisionMap) {
        // Resolve same position hostile x vulnerable collisions
        if (info.hostilePresent && info.collisionList.size() > 1U) {
            for (const auto& character : info.collisionList) {
                if (character->getInteraction() == CharacterInteraction::kVulnerable) {
                    hostileCollisionCharacterIds.emplace(character->getId());
                }
            }
        }

        // Resolve swapped position hostile x vulnerable collisions
        for (const auto& character : info.collisionList) {
            if (character->getInteraction() == CharacterInteraction::kVulnerable &&
                character->isNewPosition() &&
                isSwapWithHostile(character, collisionMap)) {
                hostileCollisionCharacterIds.emplace(character->getId());
            }
        }
    }

    return hostileCollisionCharacterIds;
}

void CharacterManager::draw(sf::RenderWindow& window) {
    for (const auto& [id, character] : mCharacters) {
        character->draw(window);
    }
}
