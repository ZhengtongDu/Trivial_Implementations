#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"

/**
 * @brief The Triangle class represents a triangle in 2D space, defined by its three vertices.
 * 
 * The vertices should be provided in counter-clockwise order.
 */
class Triangle
{
public:
    Vector2f v0, v1, v2; // vertices A, B, C, counter-clockwise order

    /**
     * @brief Constructor for the Triangle class.
     * 
     * @param _v0 The first vertex of the triangle.
     * @param _v1 The second vertex of the triangle.
     * @param _v2 The third vertex of the triangle.
     */
    Triangle(const Vector2f& _v0, const Vector2f& _v1, const Vector2f& _v2)
        : v0(_v0), v1(_v1), v2(_v2) { }

    /**
     * @brief Overloaded operator<< for the Triangle class.
     * 
     * @param os The output stream to write to.
     * @param tri The triangle to write to the output stream.
     * @return The output stream after the triangle has been written to it.
     */
    friend std::ostream& operator<<(std::ostream& os, const Triangle& tri) {
        os << "triangle: " << std::endl;
        os << "      point 0: " << tri.v0 << std::endl; 
        os << "      point 1: " << tri.v1 << std::endl; 
        os << "      point 2: " << tri.v2 << std::endl; 
        return os;
    }    
};

#endif // TRIANGLE_H
