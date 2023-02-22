#include "Draw.h"

int main(int argc, char* argv[]){

    Screen scn(1000, 1000, std::string("test"));
    Vector2f a(100, 200);
    Vector2f b(100, 500);
    Vector2f c(300, 500);
    Vector2f d(300, 200);
    std::vector<Vector2f> pointSet;
    pointSet.push_back(a);
    pointSet.push_back(b);
    pointSet.push_back(c);
    pointSet.push_back(d);
    Triangle tri(a, b, c);
    drawTriangle(tri, scn);
    //scn.screenShow();
    //scn.imageWrite("test.png");
    std::cout << tri;
    return 0;
}