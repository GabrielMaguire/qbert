#include "Pyramid.hpp"

#include "CubePosition.hpp"
#include "MathUtils.hpp"
#include "Movement.hpp"

#include "SFML/System/Vector2.hpp"

#include <cstdint>

namespace pyramid {

const sf::Vector2f Cube::kP1Offset{0.0F, -kSideLength};
const sf::Vector2f Cube::kP2Offset{kVertexXOffset, -kVertexYOffset};
const sf::Vector2f Cube::kP3Offset{kVertexXOffset, kVertexYOffset};

Cube::Cube(sf::Vector2f origin, std::uint8_t maxActivation, sf::Color topColor,
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

Pyramid::Pyramid(sf::Vector2f top) : mTop{top} {
    for (std::uint8_t y{0U}; y < kHeight; ++y) {
        for (std::uint8_t x{0U}; x < (kHeight - y); ++x) {
            const CubePosition pos{x, y};
            mCubes.emplace(pos, Cube{positionToVector(pos)});
        }
    }
}

const sf::Vector2f Pyramid::kCubeDownLeft{-kVertexXOffset, kVertexYOffset + kSideLength};
const sf::Vector2f Pyramid::kCubeDownRight{kVertexXOffset, kVertexYOffset + kSideLength};

sf::Vector2f movementToVector(Movement m) {
    static constexpr float kVertical{kSideLength * 1.5F};
    static constexpr float kHorizontal{kSideLength * 0.8660254F}; // sqrt(3)/2

    switch (m) {
    case Movement::kNone:
        return {0.0F, 0.0F};

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

void Pyramid::updatePosition(CubePosition& pos, Movement m) const {
    switch (m) {
    case Movement::kNone:
        break;

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

bool Pyramid::isPositionInBounds(const CubePosition& pos) const {
    return mCubes.find(pos) != mCubes.end();
}

sf::Vector2f Pyramid::positionToVector(const CubePosition& pos) const {
    return mTop + scalarMult(pos.x, kCubeDownRight) + scalarMult(pos.y, kCubeDownLeft);
}

sf::Vector2f Pyramid::characterPositionToVector(const CubePosition& pos) const {
    static const sf::Vector2f topFaceOffset{0.0F, -kSideLength / 2.0F};
    return positionToVector(pos) + topFaceOffset;
}

} // namespace pyramid
