#ifndef VEC2
#define VEC2

class Vec2 {
public:
    Vec2(float x = 0, float y = 0);
    float x, y;

    Vec2 operator+(const Vec2 &o) const;
    Vec2 operator+=(const Vec2 &o);
	Vec2 operator-(const Vec2 &o) const;
	Vec2 operator-=(const Vec2 &o);
	Vec2 operator*(float t) const;
	Vec2 operator*=(float t);
	Vec2 operator/(float t) const;
	Vec2 Rotate(float ang) const;
	Vec2 Norm() const;
	float operator*(const Vec2 &o) const;
	float operator^(const Vec2 &o) const;
	float Cross(const Vec2 &a, const Vec2 &b) const;
	float Dist(const Vec2 &a) const;
	float Length() const;
	float Angle() const;
    bool operator==(const Vec2 &o) const;
	bool operator<(const Vec2 &o) const;
};

#endif