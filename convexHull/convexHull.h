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

double compute_intercept(const Point2<double> &p1, const Point2<double> &p2, double yaxis)
{
  if(p1[0] >= p2[0] || yaxis <= p1[0] || yaxis >= p2[0])
    {
      cout << p1[0] << " p1[0]" << endl;
      cout << p2[0] << " p2[0]" << endl;
      cout << yaxis << " yaxis" << endl;
      cout << "Error happens when computing intercept because the input is wrong!" << endl;
      return 0;
    }
  return p1[1] + (p2[1] - p1[1])*(yaxis - p1[0])/(p2[0] - p1[0]);
}

vector<int> merge(const vector<Point2<double>> &pointVec, const vector<int> &leftVec, const vector<int> &rightVec)
{
  int ln = leftVec.size();
  int rn = rightVec.size();
  vector<int> retVec;
  int lmax = 0;
  int rmin = 0;
  // get the position of leftVec_max_x and rightVec_min_x
  for(int i = 1; i < ln; i++)
    if(pointVec[leftVec[i]][0] > lmax) lmax = i;
  for(int i = 1; i < rn; i++)
    if(pointVec[rightVec[i]][0] < rmin) rmin = i;
  // result the case that (ln == 1 || rn == 1)
  if(ln == 1)
    {
      retVec.emplace_back(leftVec[0]);
      for(int i = rmin; i < rn; i++)
        retVec.emplace_back(rightVec[i]);
      for(int i = 0; i < rmin; i++)
        retVec.emplace_back(rightVec[i]);
    }
  else if (rn == 1)
    {
      retVec.emplace_back(rightVec[0]);
      for(int i = lmax; i < ln; i++)
        retVec.emplace_back(leftVec[i]);
      for(int i = 0; i < lmax; i++)
        retVec.emplace_back(leftVec[i]);
    }
  else
    {
      int leftUp = lmax;
      int leftLow = lmax;
      int rightUp = rmin;
      int rightLow = rmin;
      double yaxis = (pointVec[leftVec[lmax]][0] + pointVec[rightVec[rmin]][0])/2.0;
      double upIntercept = (pointVec[leftVec[lmax]][1] + pointVec[rightVec[rmin]][1])/2.0;
      double lowIntercept = (pointVec[leftVec[lmax]][1] + pointVec[rightVec[rmin]][1])/2.0;
      //using mod computation to get reasonable upper tangent and lower tangent
      while((compute_intercept(pointVec[leftVec[leftUp]], pointVec[rightVec[(rightUp + 1)%rn]], yaxis) > upIntercept) || (compute_intercept(pointVec[leftVec[(leftUp - 1 + ln)%ln]], pointVec[rightVec[rightUp]], yaxis) > upIntercept))
        {
          if(compute_intercept(pointVec[leftVec[leftUp]], pointVec[rightVec[(rightUp + 1)%rn]], yaxis) > upIntercept)
            {
              rightUp  = (rightUp + 1)%rn;
              upIntercept = compute_intercept(pointVec[leftVec[leftUp]], pointVec[rightVec[rightUp]], yaxis);
            }
          else if(compute_intercept(pointVec[leftVec[(leftUp - 1 + ln)%ln]], pointVec[rightVec[rightUp]], yaxis) > upIntercept)
            {
              leftUp  = (leftUp - 1 + ln)%ln;
              upIntercept = compute_intercept(pointVec[leftVec[leftUp]], pointVec[rightVec[rightUp]], yaxis);
            }
        }

      while((compute_intercept(pointVec[leftVec[(leftLow + 1)%ln]], pointVec[rightVec[rightLow]], yaxis) < lowIntercept) || (compute_intercept(pointVec[leftVec[leftLow]], pointVec[rightVec[(rightLow - 1 + rn)%rn]], yaxis) < lowIntercept))
        {
          if(compute_intercept(pointVec[leftVec[(leftLow + 1)%ln]], pointVec[rightVec[rightLow]], yaxis) < lowIntercept)
            {
              leftLow  = (leftLow + 1)%ln;
              lowIntercept = compute_intercept(pointVec[leftVec[leftLow]], pointVec[rightVec[rightLow]], yaxis);
            }
          else if(compute_intercept(pointVec[leftVec[leftLow]], pointVec[rightVec[(rightLow - 1 + rn)%rn]], yaxis) < lowIntercept)
            {
              rightLow  = (rightLow - 1 + rn)%rn;
              lowIntercept = compute_intercept(pointVec[leftVec[leftLow]], pointVec[rightVec[rightLow]], yaxis);
            }
        }
      //      cout << "leftLow is" << leftLow << endl;
      //      cout << "rightLow is" << rightLow << endl;
      //      cout << "leftUp is" << leftUp << endl;
      //      cout << "rightUp is" << rightUp << endl;
      //      for(int i = 0; i < leftVec.size(); i++)
      //        cout << leftVec[i] << " ";
      //      cout << endl;
      //      for(int i = 0; i < rightVec.size(); i++)
      //        cout << rightVec[i] << " ";
      //      cout << endl;
      int i = leftLow;
      while(i != leftUp)
        {
          retVec.emplace_back(leftVec[i]);
          i = (i + 1)%ln;
        }
      retVec.emplace_back(leftVec[i]);
      i = rightUp;
      while(i != rightLow)
        {
          retVec.emplace_back(rightVec[i]);
          i = (i + 1)%rn;
        }
      retVec.emplace_back(rightVec[i]);
      //      for(int i = 0; i < retVec.size(); i++)
      //        cout << retVec[i] << " " << endl;
    }
  return retVec;
}

vector<int> recursive_generation(const vector<Point2<double>> &pointVec, int begin, int end)
{
  int n = end - begin + 1;
  if(n == 1) return vector<int>(1, begin);
  vector<int> leftVec = recursive_generation(pointVec, begin, begin + n/2 - 1);
  vector<int> rightVec = recursive_generation(pointVec, begin + n/2, end);
  return merge(pointVec, leftVec, rightVec);
}

vector<Point2<double>> generate_convex_hull(const vector<Point2<double>> &pointVec)
{
  int n = pointVec.size();
  AVLTree<Point2<double>> pointTree;
  for(int i = 0; i < n; i++)
      pointTree.insert(pointVec[i]);
  vector<Point2<double>> orderedPointVec;
  for(int i = 0; i < n; i++)
    orderedPointVec.emplace_back(pointTree.pop_min());
  vector<int> retIntVec = recursive_generation(orderedPointVec, 0, n - 1);
  vector<Point2<double>> retPointVec;
  for(int i = 0; i < retIntVec.size(); i++)
    retPointVec.emplace_back(orderedPointVec[retIntVec[i]]);
  return retPointVec;
}

#endif // CONVEXHULL_H
