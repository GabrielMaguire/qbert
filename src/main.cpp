#include "CharacterManager.hpp"
#include "CubePosition.hpp"
#include "GameLoopTimer.hpp"
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

    GameLoopTimer gameLoopTimer{std::chrono::milliseconds{750U}};

    pyramid::Pyramid pyramid{sf::Vector2f{window.getSize().x / 2.0F, 200.0F}};

    std::atomic_bool isPlayerAlive{true};
    std::atomic_bool isCoilyAlive{false};

    CharacterManager characterManager{pyramid};
    characterManager.createPlayer(keyHandler, gameLoopTimer, isPlayerAlive,
                                  pyramid::CubePosition{0, 0});
    characterManager.initialize();

    int cycleCount{0};
    while (window.isOpen()) {
        gameLoopTimer.begin();

        if (cycleCount % 7 == 0) {
            characterManager.createBall();
        }
        if (!isCoilyAlive) {
            characterManager.createCoily(pyramid, isCoilyAlive);
        }

        characterManager.update();

        window.clear();

        pyramid.draw(window);
        characterManager.draw(window);
        window.draw(keyStatusDrawable);

        window.display();

        ++cycleCount;

        std::this_thread::sleep_for(gameLoopTimer.getTimeToEnd_ms());

        if (!isPlayerAlive) {
            window.close();
        }
    }

    runInputHandler = false;
    inputHandler.join();

    return EXIT_SUCCESS;
}
