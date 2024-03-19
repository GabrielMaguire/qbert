#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include "Cube.hpp"
#include "CubePosition.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include <cstdint>
#include <unordered_map>

namespace pyramid {

sf::Vector2f movementToVector(Movement m);

class Pyramid {
  public:
    Pyramid(sf::Vector2f top = {0.0F, 0.0F});

    void draw(sf::RenderWindow& window) {
        for (auto& [position, cube] : mCubes) {
            cube.draw(window);
        }
    }

    sf::Vector2f characterPositionToVector(const CubePosition& pos) const;
    CubePosition getUpdatedPosition(const CubePosition& pos, Movement m) const;
    bool isPositionInBounds(const CubePosition& pos) const;

    void activate(const CubePosition& pos) { mCubes.find(pos)->second.activate(); }
    void deactivate(const CubePosition& pos) { mCubes.find(pos)->second.deactivate(); }

    static constexpr std::uint8_t kHeight{7U};

    static const sf::Vector2f kCubeDownLeft;
    static const sf::Vector2f kCubeDownRight;

  private:
    sf::Vector2f positionToVector(const CubePosition& pos) const;

    const sf::Vector2f mTop;
    std::unordered_map<CubePosition, Cube> mCubes;
};

} // namespace pyramid

#endif // PYRAMID_HPP
