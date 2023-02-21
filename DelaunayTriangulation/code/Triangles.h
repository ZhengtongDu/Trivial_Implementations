#ifndef TRIANGLES_H
#define TRIANGLES_H

#include "Vector.h"

class Triangle
{
public:
    Vector2f v0, v1, v2; // vertices A, B, C, counter-cloc,wise order
    Vector2f e0, e1, e2; // 3 edges: v1 - v0, v2 - v1, v0 - v2
    float angle0, angle1, angle2; // 3 angles corresponding to v0, v1, v2
    float sorted_angle0, sorted_angle1, sorted_angle2; // sorted_angle0 <= sorted_angle1 <= sorted_angle2

    Triangle(const Vector2f& _v0, const Vector2f& _v1, const Vector2f& _v2)
        : v0(_v0), v1(_v1), v2(_v2)
    {
        e0 = v1 - v0, e1 = v2 - v1, e2 = v0 - v2;
        angle0 = acos(e0.dotProduct(-(e2)) / (e0.norm() * e2.norm())) / PI * 180;
        angle1 = acos(e1.dotProduct(-(e0)) / (e1.norm() * e0.norm())) / PI * 180;
        angle2 = acos(e2.dotProduct(-(e1)) / (e2.norm() * e1.norm())) / PI * 180;
    }
};


#endif // TRIANGLES_H
