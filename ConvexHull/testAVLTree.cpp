#include"AVLTree.h"

using namespace std;

int main()
{
  AVLTree<int> tree;
  tree.insert(4);
  tree.print();
  cout << "---------" << endl;
  tree.insert(2);
  tree.print();
  cout << "---------" << endl;
  tree.insert(6);
  tree.print();
  cout << "---------" << endl;
  tree.insert(1);
  tree.print();
  cout << "---------" << endl;
  tree.insert(3);
  tree.print();
  cout << "---------" << endl;
  tree.insert(5);
  tree.print();
  cout << "---------" << endl;
  tree.insert(7);
  tree.print();
  cout << "---------" << endl;
  tree.pop(3);
  tree.print();
  cout << "---------" << endl;
  tree.pop(10);
  tree.print();
  cout << "---------" << endl;
  tree.pop(2);
  tree.print();
  cout << "---------" << endl;
  tree.pop(1);
  tree.print();
  return 0;
}
