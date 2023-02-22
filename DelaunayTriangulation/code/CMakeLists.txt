cmake_minimum_required(VERSION 3.10)
project(DelaunayTriangulation)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(DelaunayTriangulation main.cpp)

target_link_libraries(DelaunayTriangulation ${OpenCV_LIBRARIES})

add_executable(testVector 
testVector.cpp GLOBAL.h Vector.h Triangle.h Draw.h DelaunayTriangulation.h)

target_link_libraries(testVector ${OpenCV_LIBRARIES})
