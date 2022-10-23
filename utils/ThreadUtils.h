# pragma once
# include <thread>
# include <chrono>

void sleep(int pSeconds) {
    std::chrono::seconds time(pSeconds);
    std::this_thread::sleep_for(time);
}

void sleep(double pSeconds) {
    std::chrono::milliseconds time(int(pSeconds*1000));
    std::this_thread::sleep_for(time);
}