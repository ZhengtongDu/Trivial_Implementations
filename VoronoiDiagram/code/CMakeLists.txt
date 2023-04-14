cmake_minimum_required(VERSION 3.10)
project(DelaunayTriangulation)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(test
test.cpp GLOBAL.h Vector.h Triangle.h Draw.h DelaunayTriangulation.h VoronoiDiagram.h)

add_executable(testRBTree
testRBTree.cpp RBTree.h)

target_link_libraries(test ${OpenCV_LIBRARIES})
