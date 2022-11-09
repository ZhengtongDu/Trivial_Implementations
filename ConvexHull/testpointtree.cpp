#include "ConvexHull.h"

using namespace std;

int main()
{
  vector<Point2<double>> pointVec(0);
  for(int i = 0; i < 10; i++)
    pointVec.emplace_back(Point2<double>(10-i, i));
  generate_convex_hull(pointVec);
  //  Pointprint(ptree.root);
}
