#ifndef KEY_HANDLER_HPP
#define KEY_HANDLER_HPP

#include "SFML/Window/Keyboard.hpp"

#include <functional>
#include <vector>

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
    using KeyHandlerCallback = std::function<void(Movement)>;

    void update(const sf::Keyboard::Key& key, const bool active);

    void registerCallback(KeyHandlerCallback callback) {
        mCallbackList.emplace_back(std::move(callback));
    }

    bool isLeftActive() const { return mArrowKeys.left; }
    bool isRightActive() const { return mArrowKeys.right; }
    bool isUpActive() const { return mArrowKeys.up; }
    bool isDownActive() const { return mArrowKeys.down; }

    Movement getMovement() const { return mCurrentMovement; }

  private:
    ArrowKeys mArrowKeys;
    Movement mCurrentMovement{Movement::kNone};
    std::vector<KeyHandlerCallback> mCallbackList{};
};

#endif // KEY_HANDLER_HPP
