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
    bool left() const { return mMovementKeys.left; }
    bool right() const { return mMovementKeys.right; }
    bool up() const { return mMovementKeys.up; }
    bool down() const { return mMovementKeys.down; }

  private:
    MovementKeys mMovementKeys;
};

#endif // KEY_HANDLER_HPP
