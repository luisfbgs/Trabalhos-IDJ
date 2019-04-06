#include "Common.h"
#include <cmath>
#include <random>
#include <chrono>

std::mt19937 rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());

float randReal(float lo, float hi) {
    return std::uniform_real_distribution<float>(lo, hi)(rng);
}

int randInt(int lo, int hi) {
    return std::uniform_int_distribution<int>(lo, hi)(rng);
}

bool equals(const float a, const float b) {
    return fabs(a - b) < eps;
}

float radToDeg(float rad) {
    return rad * 180 / pi;
}

float degToRad(float deg) {
    return deg * pi / 180;
}
