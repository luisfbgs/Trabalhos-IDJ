#ifndef RECT
#define RECT

#include "Vec2.h"

class Rect {
public:
    Rect(float x = 0, float y = 0, float w = 0, float h = 0);
    Rect(Vec2 lefUp, float w = 0, float h = 0);
    Vec2 lefUp; 
    float w, h;

    Rect operator+(const Vec2 &o) const;
    Vec2 Center() const;
    bool Contains(float x, float y) const;
    float Dist(const Rect &o) const;
};


#endif