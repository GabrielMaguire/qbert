#include "KeyHandler.hpp"

void KeyHandler::update(const sf::Keyboard::Key& key, const bool active) {
    switch (key) {
    case sf::Keyboard::Key::Left:
        movement_keys_.left = active;
        break;

    case sf::Keyboard::Key::Right:
        movement_keys_.right = active;
        break;

    case sf::Keyboard::Key::Up:
        movement_keys_.up = active;
        break;

    case sf::Keyboard::Key::Down:
        movement_keys_.down = active;
        break;

    default:
        break;
    }
}
