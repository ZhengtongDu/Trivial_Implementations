#include "DelaunayTriangulation.h"

int main(int argc, char* argv[]){
//    srand((unsigned)time(nullptr));    
    srand((unsigned)time(nullptr));    

    Screen scn(1000, 1000, std::string("test"));
    Vector2f a(100, 200);
    Vector2f b(100, 500);
    Vector2f c(300, 500);
    Vector2f d(300, 200);
    Vector2f e(200, 300);
    std::vector<Vector2f> pointSet;
    pointSet.push_back(a);
    pointSet.push_back(b);
    pointSet.push_back(c);
    pointSet.push_back(d);
    pointSet.push_back(e);
    //Triangle tri(a, b, c);
    //drawTriangle(tri, scn);
    TriangleList L;

    L.triangulation(pointSet);
    L.drawTriangulation(scn);
    scn.screenShow();
    //scn.imageWrite("test.png");
    //std::cout << tri;
    return 0;
}