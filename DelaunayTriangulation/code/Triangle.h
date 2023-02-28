#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"

class Triangle
{
public:
    Vector2f v0, v1, v2; // vertices A, B, C, counter-clockwise order

    Triangle(const Vector2f& _v0, const Vector2f& _v1, const Vector2f& _v2)
        : v0(_v0), v1(_v1), v2(_v2) { }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& tri) {
        os << "triangle: " << std::endl;
        os << "      point 0: " << tri.v0 << std::endl; 
        os << "      point 1: " << tri.v1 << std::endl; 
        os << "      point 2: " << tri.v2 << std::endl; 
        return os;
    }    
};

#endif // TRIANGLE_H
