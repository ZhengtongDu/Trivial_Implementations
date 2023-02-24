#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include "Triangle.h"
#include "Draw.h"
#include <utility>

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
    void linkEdge(const ListNode*);
    void unlinkEdge(const ListNode*);

    ListNode* head;
    std::vector<std::vector<ListNode*>> edgeTable;
};

/////
// End Class Declaration
/////

/////
// Function Definition
/////

void crossLink(ListNode* lnode, TreeNode* tnode) {
    lnode->treenode = tnode;
    tnode->listnode = lnode;
}

void TriangleList::linkEdge(const ListNode* ptr) {
    Triangle tri = ptr->tri;
    std::vector<Vector2f> pointVec;
    pointVec.push_back(tri.v0);
    pointVec.push_back(tri.v1);
    pointVec.push_back(tri.v2);
    for(int i = 0; i < 3; i++)
        for(int j = i + 1; j < 3; j++) {
        }
}

void TriangleList::unlinkEdge(const ListNode* ptr) {
    Triangle tri = ptr->tri;
    std::vector<Vector2f> pointVec;
    pointVec.push_back(tri.v0);
    pointVec.push_back(tri.v1);
    pointVec.push_back(tri.v2);
    for(int i = 0; i < 3; i++)
        for(int j = i + 1; j < 3; j++) {
        }
}

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
        if(crossProduct(e1, e2) >= -EPSILON)    return true;
    }
    return false; // point lies in the right of edge(v1, v2);
}

bool inTriangle(const Vector2f& v, const Triangle& tri) {
    if(isLeft(v, tri.v0, tri.v1) == false || isLeft(v, tri.v1, tri.v2) == false || isLeft(v, tri.v2, tri.v0) == false)
        return false;
    return true;
}

void findTriangle(const Vector2f& v, const TreeNode* ptr, std::vector<ListNode*>& ptrVec) {
    if(ptr == nullptr)  return;
    if(inTriangle(v, ptr->tri) == true) std::cout << "YES" << std::endl;
    if(inTriangle(v, ptr->tri) == false) std::cout << "NO" << std::endl;
    if(inTriangle(v, ptr->tri)) {
        if(ptr->child0 == nullptr) {
            ptrVec.push_back(ptr->listnode);
            return;
        }
        else {
            findTriangle(v, ptr->child0, ptrVec);
            findTriangle(v, ptr->child1, ptrVec);
            findTriangle(v, ptr->child2, ptrVec);
        }
    }
    return ;
}

void shuffle(std::vector<Vector2f>& pointSet) {
    for(int i = 0; i < pointSet.size() * 2; i++) 
        std::swap(pointSet[1], pointSet[getRandom(2, pointSet.size() - 2)]);
}

void legalizeEdge(const Vector2f& point, std::pair<Vector2f, Vector2f>, TriangleList& L) {
    
}

void addPoint(const std::vector<Vector2f>& pointSet, const int& index, TriangleTree& tree, TriangleList& L){
    Vector2f point = pointSet[index];
    std::vector<ListNode*> ptrVec;
    findTriangle(point, tree.root, ptrVec);
    if(ptrVec.size() == 1) {
        ListNode* ptr = ptrVec[0];
        std::cout << ptr->tri << std::endl;
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
        if(new_listnode2->next != nullptr)
            new_listnode2->next->pre = new_listnode2;
        delete ptr;
    }
    else if(ptrVec.size() == 2) {
    std::cout << ptrVec[0]->tri << std::endl;
    std::cout << ptrVec[1]->tri << std::endl;
        ListNode *ptr0 = ptrVec[0], *ptr1 = ptrVec[1];
        Vector2f tri0_v0 = ptr0->tri.v0, tri0_v1 = ptr0->tri.v1, tri0_v2 = ptr0->tri.v2;
        Vector2f tri1_v0 = ptr1->tri.v0, tri1_v1 = ptr1->tri.v1, tri1_v2 = ptr1->tri.v2;
        Vector2f one_v0, one_v1, two_v0, two_v1;
        std::vector<Vector2f> tmpVec0;
        std::vector<Vector2f> tmpVec1;
        if(tri0_v0 == tri1_v0 || tri0_v0 == tri1_v1 || tri0_v0 == tri1_v2)  tmpVec0.push_back(tri0_v0);
        else tmpVec1.push_back(tri0_v0);
        if(tri0_v1 == tri1_v0 || tri0_v1 == tri1_v1 || tri0_v1 == tri1_v2)  tmpVec0.push_back(tri0_v1);
        else tmpVec1.push_back(tri0_v1);
        if(tri0_v2 == tri1_v0 || tri0_v2 == tri1_v1 || tri0_v2 == tri1_v2)  tmpVec0.push_back(tri0_v2);
        else {
            tmpVec1.push_back(tri0_v2);
            std::swap(tmpVec0[0], tmpVec0[1]);
        }
        if(tri1_v0 != tri0_v0 && tri1_v0 != tri0_v1 && tri1_v0 != tri0_v2)  tmpVec1.push_back(tri1_v0);
        else if(tri1_v1 != tri0_v0 && tri1_v1 != tri0_v1 && tri1_v1 != tri0_v2)  tmpVec1.push_back(tri1_v1);
        else tmpVec1.push_back(tri1_v2);
        TreeNode *current_treenode0 = ptr0->treenode, *current_treenode1 = ptr1->treenode;
        Triangle new_tri00(tmpVec1[0], tmpVec0[0], point), new_tri01(tmpVec0[1], tmpVec1[0], point), new_tri10(tmpVec0[0], tmpVec1[1], point), new_tri11(tmpVec1[1], tmpVec0[1], point);
        ListNode *new_listnode00 = new ListNode(new_tri00);
        ListNode *new_listnode01 = new ListNode(new_tri01);
        new_listnode00->next = new_listnode01;
        new_listnode01->pre = new_listnode00;
        ListNode *new_listnode10 = new ListNode(new_tri10);
        ListNode *new_listnode11 = new ListNode(new_tri11);
        new_listnode10->next = new_listnode11;
        new_listnode11->pre = new_listnode10;
        TreeNode *new_treenode00 = new TreeNode(new_tri00);
        TreeNode *new_treenode01 = new TreeNode(new_tri01);
        TreeNode *new_treenode10 = new TreeNode(new_tri10);
        TreeNode *new_treenode11 = new TreeNode(new_tri11);
        crossLink(new_listnode00, new_treenode00);
        crossLink(new_listnode01, new_treenode01);
        crossLink(new_listnode10, new_treenode10);
        crossLink(new_listnode11, new_treenode11);
        current_treenode0->childNum = 2;
        current_treenode0->child0 = new_treenode00;
        current_treenode0->child1 = new_treenode01;
        current_treenode1->childNum = 2;
        current_treenode1->child0 = new_treenode10;
        current_treenode1->child1 = new_treenode11;
        if(ptr0->pre == nullptr)
            L.head = new_listnode00;
        else {
            ptr0->pre->next = new_listnode00;
            new_listnode00->pre = ptr0->pre;
        }
        if(ptr1->pre == nullptr)
            L.head = new_listnode10;
        else {
            ptr1->pre->next = new_listnode10;
            new_listnode10->pre = ptr1->pre;
        }
        new_listnode01->next = ptr0->next;
        if(new_listnode01->next != nullptr)
            new_listnode01->next->pre = new_listnode01;
        new_listnode11->next = ptr1->next;
        if(new_listnode11->next != nullptr)
            new_listnode11->next->pre = new_listnode11;
        delete ptr0;
        delete ptr1;
    }
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

    edgeTable = std::vector<std::vector<ListNode*>>(pointSet.size(), std::vector<ListNode*>(pointSet.size()));
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
        std::cout << "add point " << i << ": " << pointSet[i] << std::endl;
        addPoint(pointSet, i, tree, *this);
    }

    ListNode* ptr = head;
    // remove bounding triangle
    /*
    while(ptr != nullptr) {
        if(ptr->tri.v0.x < EPSILON || ptr->tri.v1.x < EPSILON || ptr->tri.v2.x < EPSILON) {
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
    */
    // show bounding triangle
    ///*
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
    //*/
}

void drawTriangulation(const TriangleList& L, Screen& scn) {
    ListNode* ptr = L.head;
    while(ptr != nullptr) {
        drawTriangle(ptr->tri, scn);
        ptr = ptr->next;
    }
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

#endif // DELAUNAYTRIANGULATION_H