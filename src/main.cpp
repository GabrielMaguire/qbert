#include <SFML/Graphics.hpp>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>

#include "KeyHandler.hpp"

sf::Font font;

class KeyStatusDrawable : public sf::Drawable {
  public:
    KeyStatusDrawable(const KeyHandler& key_handler) : key_handler_(key_handler) {}

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        constexpr uint8_t kNumKeys{4U};
        std::array<sf::Text, kNumKeys> key_text_list{
            sf::Text{"Left : " + std::to_string(key_handler_.left()), font, 20},
            sf::Text{"Right: " + std::to_string(key_handler_.right()), font, 20},
            sf::Text{"Up   : " + std::to_string(key_handler_.up()), font, 20},
            sf::Text{"Down : " + std::to_string(key_handler_.down()), font, 20},
        };

        for (uint8_t i = 0U; i < kNumKeys; ++i) {
            key_text_list.at(i).setPosition(10.0F, (i * 20.0F) + 10.0F);
            target.draw(key_text_list.at(i));
        }
    }

    const KeyHandler& key_handler_;
};

int main() {
    if (!font.loadFromFile(std::string(FONT_DIR) + std::string("IBMPlexMono-Text.ttf"))) {
        return EXIT_FAILURE;
    }

    auto window = sf::RenderWindow{{1920U, 1080U}, "CMake SFML Project"};
    window.setFramerateLimit(144);
    window.setKeyRepeatEnabled(false);

    KeyHandler key_handler;
    KeyStatusDrawable key_status_drawable(key_handler);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                key_handler.update(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                key_handler.update(event.key.code, false);
                break;

            default:
                break;
            }
        }

        window.clear();

        window.draw(key_status_drawable);

        window.display();
    }

    return EXIT_SUCCESS;
}
