#include "CharacterManager.hpp"
#include "CubePosition.hpp"
#include "KeyHandler.hpp"
#include "KeyStatusDrawable.hpp"
#include "Player.hpp"
#include "Pyramid.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>

sf::Font font;

constexpr std::size_t kWindowWidth{1920U};
constexpr std::size_t kWindowHeight{1080U};

int main() {
    if (!font.loadFromFile(std::string(FONT_DIR) + std::string("IBMPlexMono-Text.ttf"))) {
        return EXIT_FAILURE;
    }

    auto window = sf::RenderWindow{{kWindowWidth, kWindowHeight}, "CMake SFML Project"};
    window.setFramerateLimit(144);
    window.setKeyRepeatEnabled(false);

    KeyHandler keyHandler;
    KeyStatusDrawable keyStatusDrawable(keyHandler, font);

    pyramid::Pyramid pyramid{sf::Vector2f{window.getSize().x / 2.0F, 200.0F}};

    CharacterManager characterManager{pyramid};
    characterManager.createPlayer(keyHandler, pyramid::CubePosition{0, 0});
    characterManager.createBall();
    // characterManager.createCoily();
    characterManager.initialize();

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
        characterManager.draw(window);
        window.draw(keyStatusDrawable);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return EXIT_SUCCESS;
}
