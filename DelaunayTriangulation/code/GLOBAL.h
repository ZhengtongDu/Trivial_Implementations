#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>

const float PI = 3.1415926f;
const float EPSILON = 0.0001; 
const float Infinity = std::numeric_limits<float>::max();


inline int getRandom(int start, int size = 100) {
    if(size < 0) size = 100;
    return start + rand() % size;
}

#endif // GLOBAL_H
