#ifndef CUBE_HPP
#define CUBE_HPP

#include "CubeColors.hpp"

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

#include <algorithm>
#include <cstdint>

namespace pyramid {

constexpr float kSideLength{75.0F};
constexpr float kVertexXOffset{kSideLength * 0.8660254F}; // sqrt(3)/2
constexpr float kVertexYOffset{kSideLength * 0.5F};

enum class CubeAction { kNone, kActivate, kDeactivate };

class Cube {
  public:
    Cube(sf::Vector2f origin, std::int32_t maxActivation = 1,
         std::vector<sf::Color> topFaceColors = {kLevel1TopFace, kLevel1TopFaceActivated},
         sf::Color leftFaceColor = kLevel1LeftFace,
         sf::Color rightFaceColor = kLevel1RightFace);

    bool isMaxActivation() const { return mActivation == mMaxActivation; }

    void activate() {
        mActivation = std::min(mActivation + 1, mMaxActivation);
        mTopFace.setFillColor(mTopFaceColors.at(mActivation));
    }

    void deactivate() {
        mActivation = std::max(mActivation - 1, 0);
        mTopFace.setFillColor(mTopFaceColors.at(mActivation));
    }

    void draw(sf::RenderWindow& window);

  private:
    static const sf::Vector2f kP1Offset;
    static const sf::Vector2f kP2Offset;
    static const sf::Vector2f kP3Offset;

    sf::ConvexShape mTopFace{4U};
    sf::ConvexShape mLeftFace{4U};
    sf::ConvexShape mRightFace{4U};

    std::vector<sf::Color> mTopFaceColors;

    std::int32_t mActivation{0U};
    const std::int32_t mMaxActivation;
};

} // namespace pyramid

#endif // CUBE_HPP
