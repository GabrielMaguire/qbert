#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include "CubePosition.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include <cstdint>
#include <unordered_map>

namespace pyramid {

sf::Vector2f movementToVector(Movement m);

constexpr float kSideLength{75.0F};
constexpr float kVertexXOffset{kSideLength * 0.8660254F}; // sqrt(3)/2
constexpr float kVertexYOffset{kSideLength * 0.5F};

enum class CubeAction { kNone, kActivate, kDeactivate };

class Cube {
  public:
    Cube(sf::Vector2f origin, std::uint8_t maxActivation = 1U,
         sf::Color topColor = {152U, 171U, 238U}, sf::Color leftColor = {29U, 36U, 202U},
         sf::Color rightColor = {32U, 22U, 88U});

    bool isMaxActivation() const { return mActivation == mMaxActivation; }
    void activate() { mTopFace.setFillColor({175U, 151U, 237U}); }
    void deactivate() { mTopFace.setFillColor({152U, 171U, 238U}); }
    void draw(sf::RenderWindow& window);

  private:
    static const sf::Vector2f kP1Offset;
    static const sf::Vector2f kP2Offset;
    static const sf::Vector2f kP3Offset;

    sf::ConvexShape mTopFace{4U};
    sf::ConvexShape mLeftFace{4U};
    sf::ConvexShape mRightFace{4U};

    const std::uint8_t mMaxActivation;
    uint8_t mActivation{0U};
};

class Pyramid {
  public:
    Pyramid(sf::Vector2f top = {0.0F, 0.0F});

    void draw(sf::RenderWindow& window) {
        for (auto& [position, cube] : mCubes) {
            cube.draw(window);
        }
    }

    sf::Vector2f characterPositionToVector(const CubePosition& pos) const;
    void updatePosition(CubePosition& pos, pyramid::Movement m) const;
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
