#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include"AVLTree.h"
#include"Point2.h"
#include<iostream>

using namespace std;

void print_ordered_points(const AVLTree<Point2<double>>::AVLNode* root)
{
  if(root == nullptr) return;
  print_ordered_points(root->left);
  cout << root->value << endl;
  print_ordered_points(root->right);
}

//input vector<Point2<double>> pointvec
//output vector<Point2<double>> convexhullvec

//vector<Point2<double>> generate_convex_hull(const vector<Point2<double>>& pointVec)
void generate_convex_hull(const vector<Point2<double>> &pointVec)
{
  int n = pointVec.size();
  AVLTree<Point2<double>> pointTree;
  for(int i = 0; i < n; i++)
      pointTree.insert(pointVec[i]);
  vector<Point2<double>> orderedPointVec(0);
  for(int i = 0; i < n; i++)
    orderedPointVec.emplace_back(pointTree.pop_min());
  for(int i = 0; i < n; i++)
    cout << orderedPointVec[i] << endl;
}

vector<int> merge(const vector<Point2<double>> &pointVec, const vector<int> &leftVec, const vector<int> &rightVec)
{
  return leftVec;
}

vector<int> recursive_generation(const vector<Point2<double>> &pointVec, int begin, int end)
{
  int n = end - begin + 1;
  if(n == 1) return vector<int>(1, begin);
  vector<int> leftVec = recursive_generation(pointVec, begin, begin + n/2);
  vector<int> rightVec = recursive_generation(pointVec, begin + n/2 + 1, end);
  return merge(pointVec, leftVec, rightVec);
}
#endif // CONVEXHULL_H
