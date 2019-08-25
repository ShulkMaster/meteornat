#ifndef SORTER_LIFETIMER_H
#define SORTER_LIFETIMER_H

#include <chrono>
#include <iostream>

class LifeTimer {

public:
    explicit LifeTimer(const char *functionName);

    ~LifeTimer();

    void clock();

private:
    const char *name;
    std::chrono::time_point<std::chrono::high_resolution_clock> begin;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
};


#endif //SORTER_LIFETIMER_H
