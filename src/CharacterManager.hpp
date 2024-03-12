#ifndef CHARACTER_MANAGER_HPP
#define CHARACTER_MANAGER_HPP

#include "BallEnemy.hpp"
#include "CoilyEnemy.hpp"
#include "ICharacter.hpp"
#include "Player.hpp"
#include "Pyramid.hpp"

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>

class CharacterManager {
  public:
    CharacterManager(const pyramid::Pyramid& pyramid) : mPyramid{pyramid} {}

    void initialize();
    void update();
    void draw(sf::RenderWindow& window);

    template <typename... Args> void createPlayer(Args&&... args) {
        mCharacters.emplace(createCharacterId(),
                            std::make_shared<Player>(std::forward<Args>(args)...));
    }

    template <typename... Args> void createBall(Args&&... args) {
        mCharacters.emplace(createCharacterId(),
                            std::make_shared<BallEnemy>(std::forward<Args>(args)...));
    }

    template <typename... Args> void createCoily(Args&&... args) {
        mCharacters.emplace(createCharacterId(),
                            std::make_shared<CoilyEnemy>(std::forward<Args>(args)...));
    }

  private:
    using IdType = std::uint16_t;

    IdType createCharacterId() {
        static IdType idGen{0U};
        return idGen++;
    }

    const pyramid::Pyramid& mPyramid;
    std::unordered_map<IdType, std::shared_ptr<ICharacter>> mCharacters;
};

#endif // CHARACTER_MANAGER_HPP
