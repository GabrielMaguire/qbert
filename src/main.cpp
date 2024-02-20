#include <SFML/Graphics.hpp>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>

#include "CharacterManager.hpp"
#include "KeyHandler.hpp"
#include "Player.hpp"
#include "Pyramid.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/ConvexShape.hpp"

sf::Font font;

constexpr std::size_t kWindowWidth{1920U};
constexpr std::size_t kWindowHeight{1080U};

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

    auto window = sf::RenderWindow{{kWindowWidth, kWindowHeight}, "CMake SFML Project"};
    window.setFramerateLimit(144);
    window.setKeyRepeatEnabled(false);

    KeyHandler keyHandler;
    KeyStatusDrawable key_status_drawable(keyHandler);

    pyramid::Pyramid pyramid{sf::Vector2f{window.getSize().x / 2.0F, 200.0F}};

    CharacterManager characterManager;
    characterManager.createPlayer(pyramid::CubePosition{5, 5});
    characterManager.createBall();
    characterManager.createCoily();

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                keyHandler.update(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                keyHandler.update(event.key.code, false);
                break;

            default:
                break;
            }
        }

        characterManager.update();

        window.clear();

        pyramid.draw(window);

        window.draw(key_status_drawable);
        for (auto& character : characterManager.mCharacters) {
            window.draw(character->mSprite);
        }

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return EXIT_SUCCESS;
}
