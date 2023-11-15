#ifndef KEY_HANDLER_HPP
#define KEY_HANDLER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

struct MovementKeys {
    MovementKeys() : left{false}, right{false}, up{false}, down{false} {}

    bool left : 1;
    bool right : 1;
    bool up : 1;
    bool down : 1;
};

class KeyHandler {
  public:
    void update(const sf::Keyboard::Key& key, const bool active);
    bool left() const { return movement_keys_.left; }
    bool right() const { return movement_keys_.right; }
    bool up() const { return movement_keys_.up; }
    bool down() const { return movement_keys_.down; }

  private:
    MovementKeys movement_keys_;
};

#endif // KEY_HANDLER_HPP
