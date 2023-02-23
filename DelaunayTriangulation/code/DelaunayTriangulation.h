#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include "Triangle.h"
#include "Draw.h"

struct TreeNode;
struct ListNode;

struct TreeNode{
        Triangle tri;
        TreeNode *child0, *child1, * child2;
        int childNum;
        ListNode *listnode;
        TreeNode(const Triangle& _tri)
        : tri(_tri), child0(nullptr), child1(nullptr), child2(nullptr), childNum(0) { }
};

struct ListNode{
        Triangle tri;
        ListNode *pre, *next;
        TreeNode* treenode;
        ListNode(const Triangle& _tri)
        : tri(_tri), pre(nullptr), next(nullptr) { }
};

void crossLink(ListNode* lnode, TreeNode* tnode) {
    lnode->treenode = tnode;
    tnode->listnode = lnode;
}

class TriangleTree
{
public:
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

    void drawTriangulation(Screen& scn){
        ListNode* ptr = head;
        while(ptr != nullptr){
            drawTriangle(ptr->tri, scn);
            ptr = ptr->next;
        }
    }

    void triangulation(std::vector<Vector2f>);

    ListNode* head;
};

/////
// End Class Declaration
/////

/////
// Function Definition
/////

void printTree(TreeNode* ptr) {
    if(ptr == nullptr) return;
    std::cout << ptr->tri << std::endl;
    printTree(ptr->child0);
    printTree(ptr->child1);
    printTree(ptr->child2);
}

bool isLeft(const Vector2f& point, const Vector2f& v1, const Vector2f& v2) {
    if(v1.x < 0 || v2.x < 0) {
        if(v1.x < 0 && v2.x < 0) {
            std::cout << "case 1" << std::endl;
            return true; // point lies in the left of edge(v1, v2);  
        }
        if(v1.x == -1) {
            std::cout << "case 2" << std::endl;
            if((v2.y < point.y) || (v2.y == point.y && v2.x < point.x))
                return true;
        }
        if(v2.x == -1) {
            std::cout << "case 3" << std::endl;
            if((v1.y > point.y) || (v1.y == point.y && v1.x > point.x))
                return true;
        }
        if(v1.x == -2) {
            std::cout << "case 4" << std::endl;
            if((v2.y > point.y) || (v2.y == point.y && v2.x > point.x))
                return true;
        }
        if(v2.x == -2) {
            std::cout << "case 5" << std::endl;
            if((v1.y < point.y) || (v1.y == point.y && v1.x < point.x))
                return true;
        }
    }
    else {
        Vector2f e1 = v2 - v1, e2 = point - v1;
        if(crossProduct(e1, e2) > 0)    return true;
    }
    return false; // point lies in the right of edge(v1, v2);
}

bool inTriangle(const Vector2f& v, const Triangle& tri) {
    if(isLeft(v, tri.v0, tri.v1) == false || isLeft(v, tri.v1, tri.v2) == false || isLeft(v, tri.v2, tri.v0) == false)
        return false;
    return true;
}

ListNode* findTriangle(const Vector2f& v, const TreeNode* ptr) {
    if(ptr == nullptr)  return nullptr;
    if(inTriangle(v, ptr->tri) == true) std::cout << "YES" << std::endl;
    if(inTriangle(v, ptr->tri) == false) std::cout << "NO" << std::endl;
    if(inTriangle(v, ptr->tri)) {
        if(ptr->child0 == nullptr)
            return ptr->listnode;
        ListNode* pptr;
        pptr = findTriangle(v, ptr->child0);
        if(pptr != nullptr) return pptr;
        pptr = findTriangle(v, ptr->child1);
        if(pptr != nullptr) return pptr;
        pptr = findTriangle(v, ptr->child2);
        if(pptr != nullptr) return pptr;
    }
    return nullptr;
}

inline void TriangleTree::deleteSubtree(TreeNode* ptr) {
    if(ptr != nullptr) {
        deleteSubtree(ptr->child0);
        deleteSubtree(ptr->child1);
        deleteSubtree(ptr->child2);
        delete ptr;
        ptr = nullptr;
    }
    return;
}

void shuffle(std::vector<Vector2f>& pointSet) {
    for(int i = 0; i < pointSet.size() * 2; i++) 
        std::swap(pointSet[1], pointSet[getRandom(2, pointSet.size() - 2)]);
}

void addPoint(const std::vector<Vector2f>& pointSet, const int& index, TriangleTree& tree, TriangleList& L){
    Vector2f point = pointSet[index];
    ListNode* ptr = findTriangle(point, tree.root);
    //std::cout << ptr->tri << std::endl;
    Vector2f tri_v0 = ptr->tri.v0, tri_v1 = ptr->tri.v1, tri_v2 = ptr->tri.v2;
    TreeNode *current_treenode = ptr->treenode;
    Triangle new_tri0(tri_v0, tri_v1, point), new_tri1(tri_v1, tri_v2, point), new_tri2(tri_v2, tri_v0, point);
    ListNode *new_listnode0 = new ListNode(new_tri0);
    ListNode *new_listnode1 = new ListNode(new_tri1);
    ListNode *new_listnode2 = new ListNode(new_tri2);
    TreeNode *new_treenode0 = new TreeNode(new_tri0);
    TreeNode *new_treenode1 = new TreeNode(new_tri1);
    TreeNode *new_treenode2 = new TreeNode(new_tri2);
    crossLink(new_listnode0, new_treenode0);
    crossLink(new_listnode1, new_treenode1);
    crossLink(new_listnode2, new_treenode2);
    current_treenode->childNum = 3;
    current_treenode->child0 = new_treenode0;
    current_treenode->child1 = new_treenode1;
    current_treenode->child2 = new_treenode2;
    if(ptr->pre == nullptr) 
        L.head = new_listnode0;
    else {
        ptr->pre->next = new_listnode0;
        new_listnode0->pre = ptr->pre;
    }
    new_listnode0->next = new_listnode1;
    new_listnode1->pre = new_listnode0;
    new_listnode1->next = new_listnode2;
    new_listnode2->pre = new_listnode1;
    new_listnode2->next = ptr->next;
    delete ptr;
}

// Triangulation:
// 1. shuffle P and select highest point
// 2. construct bounding triangle
// 3. for each point p_r
//    case1 listnode = find(p_r)
//          add three new triangles to list
//          remove old triangle from list
//          legalizeEdge(p_r, edge)
// 4. remove bounding triangle

void change1(float& x) {
    x = 990;
}

void change2(float& x) {
    x = 10;
}

void TriangleList::triangulation(std::vector<Vector2f> pointSet) {
    if(pointSet.size() < 3) return;

    // select highest point and shuffle point set.    
    for(int i = 1; i < pointSet.size(); i++) {
        if((pointSet[i].y > pointSet[0].y) || (pointSet[i].y == pointSet[0].y && pointSet[i].x > pointSet[0].x))
            std::swap(pointSet[i], pointSet[0]);
    }
    // shuffle(pointSet);
    // construct bounding triangle
    Vector2f p_1(-1), p_2(-2); // p_1 : the leftest and highest point, p_2 : the rightest and lowest point
    Vector2f p_0 = pointSet[0];
    Triangle boundingTri(p_1, p_2, p_0);
    head = new ListNode(boundingTri);

    TriangleTree tree;
    tree.root = new TreeNode(boundingTri);
    crossLink(head, tree.root);

    std::cout << tree.root->tri << std::endl;

//    std::cout << "point1 = " << pointSet[1] << std::endl;
//    addPoint(pointSet, 1, tree, *this);
//    std::cout << head->tri << std::endl;
//    std::cout << head->next->tri << std::endl;
//    std::cout << head->next->next->tri << std::endl;
//    std::cout << "point2 = " << pointSet[2] << std::endl;
//    addPoint(pointSet, 2, tree, *this);
    // add every point from point set
    for(int i = 1; i < pointSet.size(); i++) {
        addPoint(pointSet, i, tree, *this);
    }

    ListNode* ptr = head;
    // remove bounding triangle
    ///*
    while(ptr != nullptr) {
        if(ptr->tri.v0.x < 0 || ptr->tri.v1.x < 0 || ptr->tri.v2.x < 0) {
            if(ptr == head) {
                head = head->next;
                head->pre = nullptr;
                delete ptr;
                ptr = head;
            }
            else {
                ListNode* tmp = ptr->next;
                ptr->pre->next = ptr->next;
                ptr->next->pre = ptr->pre;
                delete ptr;
                ptr = tmp;
            }
        }
        else
            ptr = ptr->next;
    }
    //*/
    // show bounding triangle
    /*
    while(ptr != nullptr) {
        if(ptr->tri.v0.x < 0 || ptr->tri.v1.x < 0 || ptr->tri.v2.x < 0) {
            if(ptr->tri.v0.x == -1) {
                change2(ptr->tri.v0.x);
                change1(ptr->tri.v0.y);
            }
            else if(ptr->tri.v0.x == -2) {
                change1(ptr->tri.v0.x);
                change2(ptr->tri.v0.y);
            }
            if(ptr->tri.v1.x == -1) {
                change2(ptr->tri.v1.x);
                change1(ptr->tri.v1.y);
            }
            else if(ptr->tri.v1.x == -2) {
                change1(ptr->tri.v1.x);
                change2(ptr->tri.v1.y);
            }
            if(ptr->tri.v2.x == -1) {
                change2(ptr->tri.v2.x);
                change1(ptr->tri.v2.y);
            }
            else if(ptr->tri.v2.x == -2) {
                change1(ptr->tri.v2.x);
                change2(ptr->tri.v2.y);
            }
        }
        ptr = ptr->next;
    }
    */
}

void drawTriangulation(const TriangleList& L, Screen& scn) {
    ListNode* ptr = L.head;
    while(ptr != nullptr) {
        drawTriangle(ptr->tri, scn);
        ptr = ptr->next;
    }
}


#endif // DELAUNAYTRIANGULATION_H