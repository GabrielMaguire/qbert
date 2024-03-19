#include "Cube.hpp"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>

namespace pyramid {

const sf::Vector2f Cube::kP1Offset{0.0F, -kSideLength};
const sf::Vector2f Cube::kP2Offset{kVertexXOffset, -kVertexYOffset};
const sf::Vector2f Cube::kP3Offset{kVertexXOffset, kVertexYOffset};

Cube::Cube(sf::Vector2f origin, std::int32_t maxActivation,
           std::vector<sf::Color> topFaceColors, sf::Color leftFaceColor,
           sf::Color rightFaceColor)
    : mMaxActivation{maxActivation}, mTopFaceColors{std::move(topFaceColors)} {
    assert(mMaxActivation > 0);
    assert(mTopFaceColors.size() == mMaxActivation + 1);

    mTopFace.setFillColor(mTopFaceColors.front());
    mTopFace.setPoint(0U, origin);
    mTopFace.setPoint(1U, origin - kP3Offset);
    mTopFace.setPoint(2U, origin + kP1Offset);
    mTopFace.setPoint(3U, origin + kP2Offset);

    mLeftFace.setFillColor(leftFaceColor);
    mLeftFace.setPoint(0U, origin);
    mLeftFace.setPoint(1U, origin - kP1Offset);
    mLeftFace.setPoint(2U, origin - kP2Offset);
    mLeftFace.setPoint(3U, origin - kP3Offset);

    mRightFace.setFillColor(rightFaceColor);
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

} // namespace pyramid
