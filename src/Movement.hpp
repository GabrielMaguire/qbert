#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <cstdint>

namespace pyramid {

enum class Movement : uint8_t { kNone, kUpLeft, kUpRight, kDownLeft, kDownRight };

} // namespace pyramid

#endif // MOVEMENT_HPP
