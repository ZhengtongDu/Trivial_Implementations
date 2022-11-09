#include"ConvexHull.h"
//#include"AVLTree.h"
#include<vector>
using namespace std;

int main(int argc, char* argv[]){
  vector<Point2<double>> pointVec;
  pointVec.emplace_back(Point2<double>(0, 0));
  pointVec.emplace_back(Point2<double>(10, -5));
  pointVec.emplace_back(Point2<double>(20, -5));
  pointVec.emplace_back(Point2<double>(5, 10));
  pointVec.emplace_back(Point2<double>(15, 11));
  pointVec.emplace_back(Point2<double>(25, 10));
  pointVec.emplace_back(Point2<double>(6, 5));
  cout << "The input set is : ";
  for(int i = 0; i < pointVec.size(); i++)
    cout << pointVec[i] << " ";
  cout << endl;
  vector<Point2<double>> retVec = generate_convex_hull(pointVec);
  //  cout << "retVec.size() = " << retVec.size() << endl;
  cout << "The convex hull is " << endl;
  for(int i = 0; i < retVec.size(); i++)
    cout << retVec[i] << " -> ";
  cout << retVec[0];
  
  return 0;
}
