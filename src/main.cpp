#include "CharacterManager.hpp"
#include "CubePosition.hpp"
#include "KeyHandler.hpp"
#include "KeyStatusDrawable.hpp"
#include "Pyramid.hpp"

#include "SFML/Window/Event.hpp"

#include <atomic>
#include <chrono>
#include <cstdlib>
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
    characterManager.initialize();

    std::atomic_bool runInputHandler{true};

    std::thread inputHandler{[&runInputHandler, &window, &keyHandler] {
        while (runInputHandler) {
            for (sf::Event event; window.waitEvent(event);) {
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
        }
    }};

    int cycleCount{0};
    while (window.isOpen()) {
        std::chrono::steady_clock::time_point begin_loop{
            std::chrono::steady_clock::now()};

        if (cycleCount % 7 == 0) {
            characterManager.createBall();
        }
        characterManager.update();

        window.clear();

        pyramid.draw(window);
        characterManager.draw(window);
        window.draw(keyStatusDrawable);

        window.display();

        ++cycleCount;

        std::chrono::steady_clock::time_point end_processing{
            std::chrono::steady_clock::now()};
        std::chrono::duration<double, std::milli> processing_dt{end_processing -
                                                                begin_loop};

        std::this_thread::sleep_for(std::chrono::milliseconds(500U) - processing_dt);
    }

    runInputHandler = false;
    inputHandler.join();

    return EXIT_SUCCESS;
}
