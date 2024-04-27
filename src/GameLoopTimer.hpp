#ifndef GAME_LOOP_TIMER_HPP
#define GAME_LOOP_TIMER_HPP

#include <chrono>

class GameLoopTimer {
  public:
    GameLoopTimer(std::chrono::duration<double, std::milli> loopDuration_ms)
        : mLoopDuration_ms{loopDuration_ms} {}

    void begin() { mLoopBeginTime = std::chrono::steady_clock::now(); }

    std::chrono::duration<double, std::milli> getTimeSinceBegin_ms() const {
        return {std::chrono::steady_clock::now() - mLoopBeginTime};
    }

    std::chrono::duration<double, std::milli> getLoopSleepTime_ms() const {
        return {mLoopDuration_ms - getTimeSinceBegin_ms()};
    }

  private:
    std::chrono::duration<double, std::milli> mLoopDuration_ms;
    std::chrono::steady_clock::time_point mLoopBeginTime;
};

#endif
