#include "Timer.h"

Timer::Timer() {
    this->time = 0;
}

void Timer::Update(int dt) {
    this->time += dt;
}

void Timer::Restart() {
    this->time = 0;
}

int Timer::Get() {
    return this->time;
}