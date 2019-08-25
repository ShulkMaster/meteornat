#include "LifeTimer.h"

LifeTimer::LifeTimer(const char *functionName) {
    name = functionName;
    begin = std::chrono::high_resolution_clock::now();
}

LifeTimer::~LifeTimer() {
    end = std::chrono::high_resolution_clock::now();
    clock();
}

void LifeTimer::clock() {
    using namespace std::chrono;
    auto start = time_point_cast<milliseconds>(begin).time_since_epoch().count();
    auto stop = time_point_cast<milliseconds>(end).time_since_epoch().count();
    long elapse = stop - start;
    std::cout << name << ": " << elapse * 0.001l << "s" << std::endl;
}



