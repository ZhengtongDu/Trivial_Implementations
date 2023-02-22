#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include "Triangle.h"
#include "Draw.h"

class TriangleTree
{
public:
    struct TreeNode{
        Triangle tri;
        TreeNode *left, *right;
        TriangleList::ListNode *listnode;
        TreeNode(const Triangle& _tri)
        : tri(_tri), left(nullptr), right(nullptr) { }
        TreeNode(const Triangle& _tri, TreeNode *_left, TreeNode *_right)
        : tri(_tri), left(_left), right(_right) { }
    };
    TriangleTree() {}
    ~TriangleTree() {
        deleteSubtree(root);
    }

    void deleteSubtree(TreeNode*);

public:
    TreeNode *root;

};


class TriangleList
{
public:
    struct ListNode{
        Triangle tri;
        ListNode *pre, *next;
        TriangleTree::TreeNode* treenode;
        ListNode(const Triangle& _tri)
        : tri(_tri), pre(nullptr), next(nullptr) { }
    };

    void drawTriangulation(Screen& scn){
        ListNode* ptr = head;
        while(ptr != nullptr){
            drawTriangle(ptr->tri, scn);
            ptr = ptr->next;
        }
    }

    void triangulation(std::vector<Vector2f>);
    
    ListNode* head;
    ListNode* end;
};

inline void TriangleTree::deleteSubtree(TreeNode* ptr) {
    if(ptr != nullptr) {
        deleteSubtree(ptr->left);
        deleteSubtree(ptr->right);
        delete ptr;
        ptr = nullptr;
    }
    return;
}

void TriangleList::triangulation(std::vector<Vector2f> pointSet) {
    if(pointSet.size() < 3) return;
    // Get lexicographically highest point of P, then shuffle P.
    for(int i = 1; i < pointSet.size(); i++) {
        if((pointSet[i].y > pointSet[0].y) || (pointSet[i].y == pointSet[0].y && pointSet[i].x > pointSet[0].x))
            std::swap(pointSet[i], pointSet[0]);
    }
    shuffle(pointSet);

}

void shuffle(std::vector<Vector2f>& pointSet) {
    for(int i = 0; i < pointSet.size() * 2; i++)
        std::swap(pointSet[1], pointSet[getRandom(2, pointSet.size() - 2)]);
}

#endif // DELAUNAYTRIANGULATION_H