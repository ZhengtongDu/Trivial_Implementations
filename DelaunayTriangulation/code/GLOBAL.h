/**

@file GLOBAL.h
@brief This file contains global constants and inline functions used throughout the program.
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>

/**

@brief The constant value of pi.
*/
const float PI = 3.1415926f;
/**

@brief The epsilon value used for floating-point comparisons.
*/
const float EPSILON = 0.0001;
/**

@brief The maximum value of a float.
*/
const float Infinity = std::numeric_limits<float>::max();
/**

@brief Generates a random integer between start and start + size.
@param start The starting value of the range.
@param size The size of the range.
@return A random integer between start and start + size.
*/
inline int getRandom(int start, int size = 100) {
if(size < 0) size = 100;
return start + rand() % size;
}
#endif // GLOBAL_H