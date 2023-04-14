/**
 * @file Vector.h
 * @brief This file defines a 2D vector class and some useful functions for it.
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

/**
 * 2D vector class with basic operations.
 */
class Vector2f {
public:
    /**
     * Default constructor. Creates a zero vector.
     */
    Vector2f() : x(0), y(0) {}
    ~Vector2f() {}
    Vector2f(const Vector2f& other) {
        x = other.x;
        y = other.y;
    }

    Vector2f& operator=(const Vector2f& other) {
        if(&other == this)
            return *this;
        x = other.x;
        y = other.y;
        return *this;
    }

    /**
     * Constructor that initializes the vector with the given values.
     * @param x The x component of the vector.
     * @param y The y component of the vector.
     */
    Vector2f(float x, float y) : x(x), y(y) {}

    /**
     * Operator overload for vector addition.
     * @param v The vector to be added.
     * @return A new vector that is the sum of this vector and the given vector.
     */
    Vector2f operator+(const Vector2f& v) const {
        return Vector2f(x + v.x, y + v.y);
    }

    /**
     * Operator overload for vector subtraction.
     * @param v The vector to be subtracted.
     * @return A new vector that is the difference between this vector and the given vector.
     */
    Vector2f operator-(const Vector2f& v) const {
        return Vector2f(x - v.x, y - v.y);
    }

    /**
     * Operator overload for vector negation.
     * @return A new vector that is the negation of this vector.
     */
    Vector2f operator-() const {
        return Vector2f(-x, -y);
    }

    /**
     * Operator overload for scalar multiplication.
     * @param r The scalar value to be multiplied.
     * @return A new vector that is the product of this vector and the given scalar.
     */
    Vector2f operator*(const float& r) const {
        return Vector2f(x * r, y * r);
    }

    /**
     * Operator overload for scalar division.
     * @param r The scalar value to be divided.
     * @return A new vector that is the quotient of this vector and the given scalar.
     */
    Vector2f operator/(const float& r) const {
        return Vector2f(x / r, y / r);
    }

    /**
     * Operator overload for vector addition and assignment.
     * @param v The vector to be added.
     * @return A reference to this vector after the addition operation.
     */
    Vector2f& operator+=(const Vector2f& v) {
        x += v.x, y += v.y;
        return *this;
    }

    /**
     * Operator overload for vector equality comparison.
     * @param v The vector to be compared.
     * @return true if this vector is equal to the given vector, false otherwise.
     */
    bool operator==(const Vector2f& v) const {
        return x == v.x && y == v.y;
    }

    /**
     * Operator overload for vector inequality comparison.
     * @param v The vector to be compared.
     * @return true if this vector is not equal to the given vector, false otherwise.
     */
    bool operator!=(const Vector2f& v) const {
        return x != v.x || y != v.y;
    }

    /**
     * Friend function for scalar multiplication.
     * @param r The scalar value to be multiplied.
     * @param v The vector to be multiplied.
     * @return A new vector that is the product of the given scalar and vector.
     */
friend Vector2f operator*(const float& r, const Vector2f& v) {
        return Vector2f(v.x * r, v.y * r);
    }
    
    /**
     * Overloading the << operator to output the vector in the format "(x, y)".
     *
     * @param os - The output stream.
     * @param v - The vector to output.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Vector2f& v) {
        return os << "(" << v.x << ", " << v.y << ")";
    }

    /**
     * Calculate the norm (length) of the vector.
     *
     * @return The norm (length) of the vector.
     */
    float norm() const {
        return sqrt(x * x + y * y);
    }

    /**
     * Calculate the normalized vector.
     *
     * @return The normalized vector.
     */
    Vector2f normalize() const {
        float r = 1.0 / this->norm();
        return Vector2f(x * r, y * r);
    }

    /**
     * Normalize the vector.
     *
     * @return The normalized vector.
     */
    Vector2f normalized() {
        float r = 1.0 / this->norm();
        x *= r, y *= r;
        return *this;
    }

    /**
     * Calculate the dot product with another vector.
     *
     * @param b - The vector to calculate the dot product with.
     * @return The dot product.
     */
    float dotProduct(const Vector2f& b) const {
        return x * b.x + y * b.y;
    }

    /**
     * Calculate the cross product with another vector.
     * The return value is positive when the vector obtained 
     * by cross product points to the outer of the plane.
     *
     * @param b - The vector to calculate the cross product with.
     * @return The cross product.
     */
    float crossProduct(const Vector2f& b) const {
        return x * b.y - y * b.x;
    }

    float x, y;
};

/**
 * Linearly interpolate between two vectors a and b.
 *
 * @param a - The first vector.
 * @param b - The second vector.
 * @param t - The interpolation factor.
 * @return The interpolated vector.
 */
inline Vector2f lerp(const Vector2f& a, const Vector2f& b, const float t) {
    return a * (1 - t) + b * t;
}

/**
 * Calculate the dot product of two vectors.
 *
 * @param a - The first vector.
 * @param b - The second vector.
 * @return The dot product.
 */
inline float dotProduct(const Vector2f& a, const Vector2f& b) {
    return a.dotProduct(b);
}

/**
 * Calculate the cross product of two vectors.
 * The return value is positive when the vector obtained 
 * by cross product points to the outer of the plane.
 *
 * @param a - The first vector.
 * @param b - The second vector.
 * @return The cross product.
 */
inline float crossProduct(const Vector2f& a, const Vector2f& b) {
    return a.crossProduct(b);
}

#endif // VECTOR_H
