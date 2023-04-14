#include <iostream>
#include "RBTree.h"

int main() {
    RBTree<int, int> tree;

    // Insert some values into the tree
    tree.insert(5, 10);
        std::cout << "success insert" << std::endl;
    tree.insert(3, 7);
        std::cout << "success insert" << std::endl;
    tree.insert(7, 14);
        std::cout << "success insert" << std::endl;
    tree.insert(6, 12);
        std::cout << "success insert" << std::endl;
    tree.inorderTraversal();
    tree.insert(8, 16);

    return 0;
}