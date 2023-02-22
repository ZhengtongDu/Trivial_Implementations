#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <time.h>

const float PI = 3.1415926f;
const float EPSILON = 0.0001; 
const float Infinity = std::numeric_limits<float>::max();

inline int getRandom(int start, int size = 100) {
    if(size < 0) size = 100;
    srand((unsigned)time(nullptr));    
    return start + (int)size * rand() % size;
}

inline void UpdateProgress(float progress)
{
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
};

#endif // GLOBAL_H
