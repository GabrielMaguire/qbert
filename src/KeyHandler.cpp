#include "KeyHandler.hpp"

void KeyHandler::update(const sf::Keyboard::Key& key, const bool active) {
    switch (key) {
    case sf::Keyboard::Key::Left:
        mArrowKeys.left = active;
        mCurrentMovement = Movement::kLeft;
        break;

    case sf::Keyboard::Key::Right:
        mArrowKeys.right = active;
        mCurrentMovement = Movement::kRight;
        break;

    case sf::Keyboard::Key::Up:
        mArrowKeys.up = active;
        mCurrentMovement = Movement::kUp;
        break;

    case sf::Keyboard::Key::Down:
        mArrowKeys.down = active;
        mCurrentMovement = Movement::kDown;
        break;

    default:
        break;
    }

    if (!active) {
        mCurrentMovement = Movement::kNone;
    }
}
