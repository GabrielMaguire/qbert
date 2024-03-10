#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <vector>

#include "Movement.hpp"
#include "SFML/Graphics/CircleShape.hpp"

namespace pyramid {

struct CubePosition {
    int x{};
    int y{};
};

sf::Vector2f movementToVector(Movement m);
void updatePosition(CubePosition& pos, pyramid::Movement m);

constexpr float kSideLength{75.0F};
constexpr float kVertexXOffset{kSideLength * 0.8660254F}; // sqrt(3)/2
constexpr float kVertexYOffset{kSideLength * 0.5F};

class Cube {
  public:
    Cube(sf::Vector2f origin, uint8_t maxActivation = 1U,
         sf::Color topColor = {152U, 171U, 238U}, sf::Color leftColor = {29U, 36U, 202U},
         sf::Color rightColor = {32U, 22U, 88U});

    uint8_t mActivation{0U};

    sf::ConvexShape mTopFace{4U};
    sf::ConvexShape mLeftFace{4U};
    sf::ConvexShape mRightFace{4U};

    bool isActivated() const { return mActivation == mMaxActivation; }
    void draw(sf::RenderWindow& window);

  private:
    static const sf::Vector2f kP1Offset;
    static const sf::Vector2f kP2Offset;
    static const sf::Vector2f kP3Offset;

    const uint8_t mMaxActivation;
};

class Pyramid {
  public:
    Pyramid(sf::Vector2f top = {0.0F, 0.0F});

    void draw(sf::RenderWindow& window) {
        for (auto& cube : mCubes) {
            cube.draw(window);
        }
    }

    sf::Vector2f positionToVector(const CubePosition& pos) const;

    static constexpr uint8_t kHeight{7U};
    static const sf::Vector2f kCubeDownLeft;
    static const sf::Vector2f kCubeDownRight;

    const sf::Vector2f mTop;

    std::vector<Cube> mCubes;
};

} // namespace pyramid

#endif // PYRAMID_HPP
