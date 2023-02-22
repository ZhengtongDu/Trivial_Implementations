#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"

class Triangle
{
public:
    Vector2f v0, v1, v2; // vertices A, B, C, counter-cloc,wise order
    Vector2f e0, e1, e2; // 3 edges: v1 - v0, v2 - v1, v0 - v2
    float angle0, angle1, angle2; // 3 angles corresponding to v0, v1, v2
    float minAngle; // store the smallest angle

    Triangle(const Vector2f& _v0, const Vector2f& _v1, const Vector2f& _v2)
        : v0(_v0), v1(_v1), v2(_v2) {
        e0 = v1 - v0, e1 = v2 - v1, e2 = v0 - v2;
        angle0 = acos(e0.dotProduct(-(e2)) / (e0.norm() * e2.norm())) / PI * 180;
        angle1 = acos(e1.dotProduct(-(e0)) / (e1.norm() * e0.norm())) / PI * 180;
        angle2 = acos(e2.dotProduct(-(e1)) / (e2.norm() * e1.norm())) / PI * 180;
        minAngle = angle0 > angle1 ? angle1 : angle0;
        minAngle = minAngle > angle2 ? angle2 : minAngle;
    }

    bool operator <(const Triangle &b) {
        return(minAngle < b.minAngle);
    }
    bool operator <=(const Triangle &b) {
        return(minAngle <= b.minAngle);
    }
    bool operator >(const Triangle &b) {
        return(minAngle > b.minAngle);
    }
    bool operator >=(const Triangle &b) {
        return(minAngle >= b.minAngle);
    }

    friend std::ostream& operator<<(std::ostream& os, const Triangle& tri) {
        os << "triangle: " << std::endl;
        os << "      point 0: " << tri.v0 << std::endl; 
        os << "      point 1: " << tri.v1 << std::endl; 
        os << "      point 2: " << tri.v2 << std::endl; 
        return os;
    }    
};

bool insideTriangle(const Vector2f& v, const Triangle& tri){
    Vector2f e0 = v - tri.v0, e1 = v - tri.v1, e2 = v - tri.v2;
    float cpro0 = crossProduct(e0, tri.e0), cpro1 = crossProduct(e1, tri.e1), cpro2 = crossProduct(e2, tri.e2); // crossProduct
    if(cpro0 >= 0 && cpro1 >= 0 && cpro2 >= 0)
        return true;
    if(cpro0 <= 0 && cpro1 <= 0 && cpro2 <= 0)
        return true;
    return false;
}

#endif // TRIANGLE_H
