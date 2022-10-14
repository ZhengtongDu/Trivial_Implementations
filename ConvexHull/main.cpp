#include"Point2.h"
#include"AVLTree.h"
#include<vector>
using namespace std;

int main(int argc, char* argv[]){
  vector<Point2<int>> a(10);
  for(int i = 0; i < 10; i++)
    a[i]=(Point2<int>(i,i))*i;
  for(int i = 0; i < 10; i++)
    cout << i << " " << a[i].x << " " << a[i].y << endl;


  return 0;
}
