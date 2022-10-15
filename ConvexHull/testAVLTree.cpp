#include"AVLTree.h"

using namespace std;

int main()
{
  AVLTree<int> tree;
  int n = 20;
  for(int i = 0; i < n; i++){
    tree.insert(i);
    tree.insert(100 - i);
    tree.insert(20 + i);
    tree.insert(60 - i);
  }
  tree.print();
  for(int i = 0; i < n*2; i++){
    tree.pop_max();
    tree.pop_min();
  }
  tree.print();
  
  return 0;
}
