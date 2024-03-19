#include "Pyramid.hpp"

#include "Cube.hpp"
#include "CubeColors.hpp"
#include "CubePosition.hpp"
#include "MathUtils.hpp"
#include "Movement.hpp"

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

#include <cstdint>

namespace pyramid {

Pyramid::Pyramid(sf::Vector2f top) : mTop{top} {
    for (std::uint8_t y{0U}; y < kHeight; ++y) {
        for (std::uint8_t x{0U}; x < (kHeight - y); ++x) {
            const CubePosition pos{x, y};

            std::vector<sf::Color> colors{
                kLevel1TopFace, kLevel1TopFaceActivated, {249U, 66U, 158U}};

            mCubes.emplace(pos, Cube{positionToVector(pos), 2, colors});
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

CubePosition Pyramid::getUpdatedPosition(const CubePosition& pos, Movement m) const {
    auto result{pos};

    switch (m) {
    case Movement::kNone:
        break;

    case Movement::kUpLeft:
        result.x -= 1;
        break;

    case Movement::kUpRight:
        result.y -= 1;
        break;

    case Movement::kDownLeft:
        result.y += 1;
        break;

    case Movement::kDownRight:
        result.x += 1;
        break;
    }

    return result;
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
