#include "DelaunayTriangulation.h"

int main(int argc, char* argv[]){
//    srand((unsigned)time(nullptr));    
    srand((unsigned)time(nullptr));    

    Vector2f b(800, 800);
    Vector2f c(600, 600);
    Vector2f d(600, 800);
    Vector2f e(800, 600);
    Vector2f a(700, 700);
    Vector2f f(750, 750);
    Vector2f g(700, 750);
    Vector2f h(550, 700);
    Vector2f i(600, 700);
    Vector2f j(650, 700);

    std::vector<Vector2f> pointSet;
    pointSet.push_back(b);
    pointSet.push_back(c);
    pointSet.push_back(d);
    pointSet.push_back(e);
    pointSet.push_back(a);
    pointSet.push_back(f);
    pointSet.push_back(g);
//    pointSet.push_back(h);
//    pointSet.push_back(i);
//    pointSet.push_back(j);
    //Triangle tri(a, b, c);
    //drawTriangle(tri, scn);
    TriangleList L;

    L.triangulation(pointSet);
    for(int i = 0; i < pointSet.size(); i++) 
        std::cout << pointSet[i] << std::endl;
    //L.printEdgeTable();
    //Screen scn(1000, 1000, std::string("test"));

    //L.drawTriangulation(pointSet, scn);
    //scn.imageWrite("test.png");
    //scn.screenShow();

    //std::cout << tri;
    ListNode* ptr = L.head;
    while(ptr->next != nullptr) {
        ptr = ptr->next;
        delete ptr->pre;
    }
    delete ptr;
    return 0;
}