#ifndef COMMON
#define COMMON

#include <cmath>

const float eps = 1e-6;
const float pi = acos(-1);

float randReal(float lo, float hi);

int randInt(int lo, int hi);

bool equals(const float a, const float b);

float radToDeg(float rad);

float degToRad(float deg);

#endif