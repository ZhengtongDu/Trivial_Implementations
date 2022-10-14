#include"AVLTree.h"

using namespace std;

int main()
{
  AVLTree<int> tree;
  for(int i = 0; i < 9; i++){
    tree.insert(i);
    tree.print();
    tree.insert(20 - i);
    tree.print();
    cout << "========="<< i << endl;
  }
  //  tree.print();
    for(int i = 0; i < 9; i++){
      tree.pop(i);
    //    tree.pop(20 - i);
    }
  tree.print();
  
  return 0;
}
