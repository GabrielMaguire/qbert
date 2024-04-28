#ifndef GAME_LOOP_TIMER_HPP
#define GAME_LOOP_TIMER_HPP

#include <chrono>

class GameLoopTimer {
  public:
    using DurationMilliseconds = std::chrono::duration<double, std::milli>;

    GameLoopTimer(DurationMilliseconds loopDuration_ms)
        : kLoopDuration_ms{loopDuration_ms} {}

    void begin() { mLoopBeginTime = std::chrono::steady_clock::now(); }

    DurationMilliseconds getTimeFromBegin_ms() const {
        return {std::chrono::steady_clock::now() - mLoopBeginTime};
    }

    DurationMilliseconds getTimeToEnd_ms() const {
        return {kLoopDuration_ms - getTimeFromBegin_ms()};
    }

    const DurationMilliseconds kLoopDuration_ms;

  private:
    std::chrono::steady_clock::time_point mLoopBeginTime;
};

#endif
