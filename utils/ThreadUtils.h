# pragma once
# include <thread>
# include <chrono>

inline void sleep(int pSeconds) {
    std::this_thread::yield();
    std::chrono::seconds time(pSeconds);
    std::this_thread::sleep_for(time);
}

inline void sleep(double pSeconds) {
    std::this_thread::yield();
    std::chrono::milliseconds time(int(pSeconds*1000));
    std::this_thread::sleep_for(time);
}