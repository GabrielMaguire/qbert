#include "Movement.hpp"

#include <functional>
#include <random>

pyramid::Movement getRandomDownwardMovement() {
    static auto gen =
        std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
    return gen() ? pyramid::Movement::kDownLeft : pyramid::Movement::kDownRight;
}

pyramid::Movement getRandomUpwardMovement() {
    static auto gen =
        std::bind(std::uniform_int_distribution<>(0, 1), std::default_random_engine());
    return gen() ? pyramid::Movement::kUpLeft : pyramid::Movement::kUpRight;
}
