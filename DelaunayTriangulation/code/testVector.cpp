#include "DelaunayTriangulation.h"

std::vector<Vector2f> pointSet;

int height = 1000;
int width = 1000;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << height - y << ")" << '\n';
        pointSet.emplace_back(x, height - y);
    }     
}

int main(int argc, char* argv[]){
//    srand((unsigned)time(nullptr));    
    Screen scn(width, height, std::string("test"));
    cv::setMouseCallback("test", mouse_handler, nullptr);
    srand((unsigned)time(nullptr));    
    TriangleList L;

    int key = -1;
    while(key != 27) {
        for (auto &point : pointSet) {
            cv::Point2f _point(point.x, height - point.y);
            cv::circle(scn.window, _point, 3, {255, 255, 255}, 3);
        }
        cv::imshow(scn.windowName, scn.window);
        key = cv::waitKey(20);
    }
    L.triangulation(pointSet);
    for(int i = 0; i < pointSet.size(); i++) 
        std::cout << pointSet[i] << std::endl;

    L.drawTriangulation(pointSet, scn);
    key = -1;
    while(key != 27) {
        cv::imshow(scn.windowName, scn.window);
        key = cv::waitKey(0);
    }

    return 0;
}

/*  Vector2f b(800, 800);
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
    pointSet.push_back(h);
    pointSet.push_back(i);
    pointSet.push_back(j);
*/
    //Triangle tri(a, b, c);
    //drawTriangle(tri, scn);
