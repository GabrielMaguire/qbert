#ifndef KEY_STATUS_DRAWABLE_HPP
#define KEY_STATUS_DRAWABLE_HPP

#include "KeyHandler.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>
#include <cstdint>

class KeyStatusDrawable : public sf::Drawable {
  public:
    KeyStatusDrawable(const KeyHandler& key_handler, const sf::Font& font)
        : mKeyHandler{key_handler}, mFont{font} {}

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        constexpr uint8_t kNumKeys{4U};
        std::array<sf::Text, kNumKeys> keyTextList{
            sf::Text{"Left : " + std::to_string(mKeyHandler.left()), mFont, 20},
            sf::Text{"Right: " + std::to_string(mKeyHandler.right()), mFont, 20},
            sf::Text{"Up   : " + std::to_string(mKeyHandler.up()), mFont, 20},
            sf::Text{"Down : " + std::to_string(mKeyHandler.down()), mFont, 20},
        };

        for (uint8_t i = 0U; i < kNumKeys; ++i) {
            keyTextList.at(i).setPosition(10.0F, (i * 20.0F) + 10.0F);
            target.draw(keyTextList.at(i));
        }
    }

    const KeyHandler& mKeyHandler;
    const sf::Font& mFont;
};

#endif // KEY_STATUS_DRAWABLE_HPP
