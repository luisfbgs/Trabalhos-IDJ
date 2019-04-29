#include <cmath>
#include "Vec2.h"
#include "Common.h"

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::operator+(const Vec2 &o) const {
    return {this->x + o.x, this->y + o.y};
}

Vec2 Vec2::operator+=(const Vec2 &o) {
    *this = *this + o;
    return *this;
}

Vec2 Vec2::operator-(const Vec2 &o) const {
    return {this->x - o.x, this->y - o.y};
}

Vec2 Vec2::operator-=(const Vec2 &o) {
    *this = *this - o;
    return *this;
}

Vec2 Vec2::operator*(float t) const {
    return {this->x * t, this->y * t};
}

Vec2 Vec2::operator*=(float t) {
    *this = *this * t;
    return *this;
}

Vec2 Vec2::operator/(float t) const {
    return {this->x / t, this->y / t};
}

Vec2 Vec2::Rotate(float ang) const {
    float rad = degToRad(ang);
    return {this->x * cosf(rad) - this->y * sinf(rad),
            this->y * cosf(rad) + this->x * sinf(rad)};
}

Vec2 Vec2::Norm() const {
    return *this / this->Length();
}

float Vec2::Angle() const {
    return radToDeg(atan2(this->y, this->x));
}

float Vec2::operator*(const Vec2 &o) const {
    return this->x * o.x + this->y * o.y;
}

float Vec2::operator^(const Vec2 &o) const {
    return this->x * o.y - this->y * o.x;
}

float Vec2::Length() const {
    return hypot(this->x, this->y);
}

float Vec2::Cross(const Vec2 &a, const Vec2 &b) const {
    return (a-(*this)) ^ (b-(*this));
}

float Vec2::Dist(const Vec2 &a) const {
    return (a-(*this)).Length();
}

bool Vec2::operator==(const Vec2 &o) const {
    return equals(x, o.x) && equals(y, o.y);
}

bool Vec2::operator<(const Vec2 &o) const {
    if(!equals(x, o.x)) return x < o.x;
    return y < o.y;
}

