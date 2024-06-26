#ifndef CHARACTER_MANAGER_HPP
#define CHARACTER_MANAGER_HPP

#include "BallEnemy.hpp"
#include "Character.hpp"
#include "CoilyEnemy.hpp"
#include "Player.hpp"
#include "Pyramid.hpp"

#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

class CharacterManager {
  public:
    CharacterManager(pyramid::Pyramid& pyramid) : mPyramid{pyramid} {}

    void initialize();
    void update();
    void draw(sf::RenderWindow& window);

    template <typename... Args> void createPlayer(Args&&... args) {
        const Character::IdType id{createCharacterId()};
        mCharacters.emplace(id,
                            std::make_shared<Player>(id, std::forward<Args>(args)...));
    }

    template <typename... Args> void createBall(Args&&... args) {
        const Character::IdType id{createCharacterId()};
        mCharacters.emplace(id,
                            std::make_shared<BallEnemy>(id, std::forward<Args>(args)...));
    }

    template <typename... Args> void createCoily(Args&&... args) {
        const Character::IdType id{createCharacterId()};
        mCharacters.emplace(
            id, std::make_shared<CoilyEnemy>(id, std::forward<Args>(args)...));
    }

  private:
    using CollisionList = std::vector<std::shared_ptr<Character>>;
    struct PositionInfo {
        bool hostilePresent{false};
        CollisionList collisionList;
    };
    using CollisionMap = std::unordered_map<pyramid::CubePosition, PositionInfo>;

    Character::IdType createCharacterId() {
        static Character::IdType idGen{0U};
        return idGen++;
    }

    std::set<Character::IdType>
    getHostileCharacterCollisions(const CollisionMap& collisionMap) const;

    void addCharacterToCollisionMap(CollisionMap& collisionMap,
                                    const std::shared_ptr<Character>& character) const;

    pyramid::Pyramid& mPyramid;
    std::unordered_map<Character::IdType, std::shared_ptr<Character>> mCharacters;
};

#endif // CHARACTER_MANAGER_HPP
