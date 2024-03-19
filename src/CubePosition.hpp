#ifndef CUBE_POSITION_HPP
#define CUBE_POSITION_HPP

#include <cstddef>
#include <cstdint>
#include <functional>

namespace pyramid {

struct CubePosition {
    std::int16_t x{};
    std::int16_t y{};
};

inline bool operator==(const CubePosition& lhs, const CubePosition& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

inline bool operator!=(const CubePosition& lhs, const CubePosition& rhs) {
    return (lhs.x != rhs.x) || (lhs.y != rhs.y);
}

} // namespace pyramid

template <> struct std::hash<pyramid::CubePosition> {
    std::size_t operator()(const pyramid::CubePosition& pos) const noexcept {
        return std::hash<std::int16_t>{}(pos.x) ^ (std::hash<std::int16_t>{}(pos.y) << 1);
    }
};

template <> struct std::less<pyramid::CubePosition> {
    constexpr bool operator()(const pyramid::CubePosition& lhs,
                              const pyramid::CubePosition& rhs) const {
        if (lhs.x == rhs.x) {
            return lhs.y < rhs.y;
        }
        return lhs.x < rhs.x;
    }
};

#endif // CUBE_POSITION_HPP
