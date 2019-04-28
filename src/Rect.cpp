#include "Rect.h"
#include "Vec2.h"

Rect::Rect(float x, float y, float w, float h) : lefUp(x, y), w(w), h(h) {}

Rect::Rect(Vec2 lefUp, float w, float h) : lefUp(lefUp), w(w), h(h) {}

Rect Rect::operator+(const Vec2 &o) const {
    return {this->lefUp + o, w, h};
}

Rect Rect::operator-(const Vec2 &o) const {
    return {this->lefUp - o, w, h};
}

Vec2 Rect::Center() const {
    return {this->lefUp.x + this->w / 2,
            this->lefUp.y + this->h / 2};
}

void Rect::CenterIn(const Vec2 &pos) {
    this->lefUp = pos;
    this->lefUp += pos - this->Center(); 
}

bool Rect::Contains(float x, float y) const {
    return (x >= this->lefUp.x && x <= this->lefUp.x + this->w
            && y >= this->lefUp.y && y <= this->lefUp.y + this->h);
}

float Rect::Dist(const Rect &o) const {
    return this->Center().Dist(o.Center());
}