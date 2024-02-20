#include "Pyramid.hpp"

#include <SFML/System/Vector2.hpp>

#include "Movement.hpp"

namespace pyramid {

namespace cube {

const sf::Vector2f Cube::kP1Offset{0.0F, -kSideLength};
const sf::Vector2f Cube::kP2Offset{kVertexXOffset, -kVertexYOffset};
const sf::Vector2f Cube::kP3Offset{kVertexXOffset, kVertexYOffset};

Cube::Cube(sf::Vector2f origin, uint8_t maxActivation, sf::Color topColor,
           sf::Color leftColor, sf::Color rightColor)
    : mMaxActivation{maxActivation} {
    mTopFace.setFillColor(topColor);
    mTopFace.setPoint(0U, origin);
    mTopFace.setPoint(1U, origin - kP3Offset);
    mTopFace.setPoint(2U, origin + kP1Offset);
    mTopFace.setPoint(3U, origin + kP2Offset);

    mLeftFace.setFillColor(leftColor);
    mLeftFace.setPoint(0U, origin);
    mLeftFace.setPoint(1U, origin - kP1Offset);
    mLeftFace.setPoint(2U, origin - kP2Offset);
    mLeftFace.setPoint(3U, origin - kP3Offset);

    mRightFace.setFillColor(rightColor);
    mRightFace.setPoint(0U, origin);
    mRightFace.setPoint(1U, origin + kP2Offset);
    mRightFace.setPoint(2U, origin + kP3Offset);
    mRightFace.setPoint(3U, origin - kP1Offset);
}

void Cube::draw(sf::RenderWindow& window) {
    window.draw(mTopFace);
    window.draw(mLeftFace);
    window.draw(mRightFace);
}

} // namespace cube

sf::Vector2f movementToVector(Movement m) {
    static constexpr float kVertical{cube::kSideLength * 1.5F};
    static constexpr float kHorizontal{cube::kSideLength * 0.8660254F}; // sqrt(3)/2

    switch (m) {
    case Movement::kUpLeft:
        return {-kHorizontal, -kVertical};

    case Movement::kUpRight:
        return {kHorizontal, -kVertical};

    case Movement::kDownLeft:
        return {-kHorizontal, kVertical};

    case Movement::kDownRight:
        return {kHorizontal, kVertical};
    }
}

void updateCubePosition(CubePosition& pos, Movement m) {
    switch (m) {
    case Movement::kUpLeft:
        pos.x -= 1;
        break;

    case Movement::kUpRight:
        pos.y -= 1;
        break;

    case Movement::kDownLeft:
        pos.y += 1;
        break;

    case Movement::kDownRight:
        pos.x += 1;
        break;
    }
}

sf::Vector2f cubePositionToVector(const CubePosition& pos) { return {}; }

} // namespace pyramid
