#ifndef KEY_HANDLER_HPP
#define KEY_HANDLER_HPP

#include <SFML/Window/Keyboard.hpp>

enum class Movement { kNone, kLeft, kRight, kUp, kDown };

struct ArrowKeys {
    ArrowKeys() : left{false}, right{false}, up{false}, down{false} {}

    bool left : 1;
    bool right : 1;
    bool up : 1;
    bool down : 1;
};

class KeyHandler {
  public:
    void update(const sf::Keyboard::Key& key, const bool active);

    bool left() const { return mArrowKeys.left; }
    bool right() const { return mArrowKeys.right; }
    bool up() const { return mArrowKeys.up; }
    bool down() const { return mArrowKeys.down; }

    Movement getMovement() const { return mCurrentMovement; }

  private:
    ArrowKeys mArrowKeys;
    Movement mCurrentMovement{Movement::kNone};
};

#endif // KEY_HANDLER_HPP
