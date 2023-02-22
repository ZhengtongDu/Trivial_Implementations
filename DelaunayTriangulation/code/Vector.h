#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>
#include "GLOBAL.h"

class Vector2f
{
public:
    Vector2f():x(0), y(0) { }
    Vector2f(const float& _x): x(_x), y(_x) { }
    Vector2f(const float& _x, const float& _y): x(_x), y(_y){ }
    Vector2f operator*(const float& r) const {
        return Vector2f(x * r, y * r);
    }
    Vector2f operator/(const float& r) const {
        if(r == 0)  throw "Division by zero condition!";
        return Vector2f(x / r, y / r);
    }
    Vector2f operator+(const Vector2f& v) const {
        return Vector2f(x + v.x, y + v.y);
    }
    Vector2f operator-(const Vector2f& v) const {
        return Vector2f(x - v.x, y - v.y);
    }
    Vector2f operator-() const
    {
        return Vector2f(-x, -y);
    }
    Vector2f operator+=(const Vector2f& v) {
        x += v.x, y += v.y;
        return *this;
    }
    friend Vector2f operator*(const float& r, const Vector2f& v) {
        return Vector2f(v.x * r, v.y * r);
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }

    float norm() const {
        return sqrt(x * x + y * y);
    }

    Vector2f normalize() const {
        float r = 1.0 / this->norm();
        return Vector2f(x * r, y * r);
    }

    Vector2f normalized() {
        float r = 1.0 / this->norm();
        x *= r, y *= r;
        return *this;
    }

    float dotProduct(const Vector2f& b) const {
        return x * b.x + y * b.y;
    }

    // Return value is positive when the vector obtained 
    // by cross product points to the outer of plane.
    float crossProduct(const Vector2f& b) const {
        return x * b.y - y * b.x;
    }

    float x, y;
};

inline Vector2f lerp(const Vector2f& a, const Vector2f& b, const float t) {
    return a * (1 - t) + b * t;
}

inline float dotProduct(const Vector2f& a, const Vector2f& b) {
    return a.dotProduct(b);
}

// Return value is positive when the vector obtained 
// by cross product points to the outer of plane.
inline float crossProduct(const Vector2f& a, const Vector2f& b) {
    return a.crossProduct(b);
}

#endif // VECTOR_H