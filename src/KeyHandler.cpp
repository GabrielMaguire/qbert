#include "KeyHandler.hpp"

void KeyHandler::update(const sf::Keyboard::Key& key, const bool active) {
    switch (key) {
    case sf::Keyboard::Key::Left:
        mMovementKeys.left = active;
        break;

    case sf::Keyboard::Key::Right:
        mMovementKeys.right = active;
        break;

    case sf::Keyboard::Key::Up:
        mMovementKeys.up = active;
        break;

    case sf::Keyboard::Key::Down:
        mMovementKeys.down = active;
        break;

    default:
        break;
    }
}
