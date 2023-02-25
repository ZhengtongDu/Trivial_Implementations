#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include "Triangle.h"
#include "Draw.h"
#include <utility>

struct TreeNode;
struct ListNode;

struct TreeNode{
    int tri_v0, tri_v1, tri_v2;
    TreeNode *child0, *child1, * child2;
    int childNum;
    ListNode *listnode;
    TreeNode(int _v0, int _v1, int _v2)
    : tri_v0(_v0), tri_v1(_v1), tri_v2(_v2), child0(nullptr), child1(nullptr), child2(nullptr), childNum(0) { }
};

struct ListNode{
    int tri_v0, tri_v1, tri_v2;
    ListNode *pre, *next;
    TreeNode* treenode;
    ListNode(int _v0, int _v1, int _v2)
    : tri_v0(_v0), tri_v1(_v1), tri_v2(_v2), pre(nullptr), next(nullptr) { }
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
    void addPoint(const std::vector<Vector2f>&, const int&, TriangleTree&, TriangleList&);
    void triangulation(std::vector<Vector2f>&);
    void drawTriangulation(const std::vector<Vector2f>& pointSet, Screen& scn);
    void linkEdge(ListNode*);
    void unlinkEdge(const int, const int, ListNode* ptr);
    void unlinkEdge(ListNode* ptr);
    void legalizeEdge(const int, const int, const int, const std::vector<Vector2f>&);
    void printEdgeTable();
    ListNode* head;
    std::vector<std::vector<std::vector<ListNode*>>> edgeTable;
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

void TriangleList::linkEdge(ListNode* ptr) {
    int ind0 = ptr->tri_v0 + 2, ind1 = ptr->tri_v1 + 2, ind2 = ptr->tri_v2 + 2;
    edgeTable[ind0][ind1].push_back(ptr);
    edgeTable[ind1][ind0].push_back(ptr);
    edgeTable[ind0][ind2].push_back(ptr);
    edgeTable[ind2][ind0].push_back(ptr);
    edgeTable[ind1][ind2].push_back(ptr);
    edgeTable[ind2][ind1].push_back(ptr);
}

void TriangleList::unlinkEdge(const int ind0, const int ind1, ListNode* ptr) {
    int i = 0;
    for(;i < edgeTable[ind0 + 2][ind1 + 2].size(); i++)
        if(edgeTable[ind0 + 2][ind1 + 2][i] == ptr) break;
    edgeTable[ind0 + 2][ind1 + 2].erase(edgeTable[ind0 + 2][ind1 + 2].begin() + i);
    edgeTable[ind1 + 2][ind0 + 2].erase(edgeTable[ind1 + 2][ind0 + 2].begin() + i);
}

void TriangleList::unlinkEdge(ListNode* ptr) {
    unlinkEdge(ptr->tri_v0, ptr->tri_v1, ptr);
    unlinkEdge(ptr->tri_v1, ptr->tri_v2, ptr);
    unlinkEdge(ptr->tri_v2, ptr->tri_v0, ptr);
}

void printTree(TreeNode* ptr) {
    if(ptr == nullptr) return;
    std::cout << ptr->tri_v0 << " " << ptr->tri_v1 << " " << ptr->tri_v2 << std::endl;
    printTree(ptr->child0);
    printTree(ptr->child1);
    printTree(ptr->child2);
}

bool isLeft(const int indr, const int ind1, const int ind2, const std::vector<Vector2f>& pointSet) {
    Vector2f v1, v2, point;
    if(ind1 >= 0)
        v1 = pointSet[ind1];
    if(ind2 >= 0)
        v2 = pointSet[ind2];
    if(indr >= 0)
        point = pointSet[indr];
    if(indr == -1) {
        if(ind2 == -2)  return false;
        if(ind1 == -2)  return true;
        if((v1.y > v2.y) || (v1.y == v2.y && v1.x > v2.x)) return true;
        return false;
    }
    if(indr == -2) {
        if(ind2 == -1)  return false;
        if(ind1 == -1)  return true;
        if((v1.y > v2.y) || (v1.y == v2.y && v1.x > v2.x)) return false;
        return true;
    }
    if(ind1 < 0 || ind2 < 0) {
        if(ind1 < 0 && ind2 < 0) {
            std::cout << "case 1" << std::endl;
            return true; // point lies in the left of edge(v1, v2);  
        }
        if(ind1 == -1) {
            std::cout << "case 4" << std::endl;
            if((v2.y > point.y) || (v2.y == point.y && v2.x > point.x))
                return true;
        }
        if(ind2 == -1) {
            std::cout << "case 5" << std::endl;
            if((v1.y < point.y) || (v1.y == point.y && v1.x < point.x))
                return true;
        }
        if(ind1 == -2) {
            std::cout << "case 2" << std::endl;
            if((v2.y < point.y) || (v2.y == point.y && v2.x < point.x))
                return true;
        }
        if(ind2 == -2) {
            std::cout << "case 3" << std::endl;
            if((v1.y > point.y) || (v1.y == point.y && v1.x > point.x))
                return true;
        }
    }
    else {
        Vector2f e1 = v2 - v1, e2 = point - v1;
        if(crossProduct(e1, e2) >= -EPSILON)    return true;
    }
    return false; // point lies in the right of edge(v1, v2);
}

bool inTriangle(const int indr, const int ind0, const int ind1, const int ind2, const std::vector<Vector2f>& pointSet) {
    if(isLeft(indr, ind0, ind1, pointSet) == false || isLeft(indr, ind1, ind2, pointSet) == false || isLeft(indr, ind2, ind0, pointSet) == false)
        return false;
    return true;
}

void findTriangle(const int indr, const TreeNode* ptr, std::vector<ListNode*>& ptrVec, const std::vector<Vector2f>& pointSet) {
    if(ptr == nullptr)  return;
    if(inTriangle(indr, ptr->tri_v0, ptr->tri_v1, ptr->tri_v2, pointSet)) {
        if(ptr->child0 == nullptr) {
            ptrVec.push_back(ptr->listnode);
            return;
        }
        else {
            findTriangle(indr, ptr->child0, ptrVec, pointSet);
            findTriangle(indr, ptr->child1, ptrVec, pointSet);
            findTriangle(indr, ptr->child2, ptrVec, pointSet);
        }
    }
    return ;
}

void shuffle(std::vector<Vector2f>& pointSet) {
    for(int i = 0; i < pointSet.size() * 2; i++) 
        std::swap(pointSet[1], pointSet[getRandom(2, pointSet.size() - 2)]);
}

inline void TriangleList::printEdgeTable() {
    for(int i = 0; i < edgeTable.size(); i++)
        for(int j = i + 1; j < edgeTable[i].size(); j++)
            for(int k = 0; k < edgeTable[i][j].size(); k++) {
                std::cout << "i: " << i - 2 << ", j: " << j - 2 << ", k: " << k + 1 << ", size = " << edgeTable[i][j].size() << ", value: ";
                std::cout << edgeTable[i][j][k]->tri_v0 << " " << edgeTable[i][j][k]->tri_v1 << " " << edgeTable[i][j][k]->tri_v2 << std::endl;
            }
}

bool isConvex(int indr, int ind0, int ind1, int indl, const std::vector<Vector2f>& pointSet){
    bool flag0, flag1;
    flag0 = isLeft(ind0, indr, indl, pointSet);
    flag1 = isLeft(ind1, indr, indl, pointSet);
    return flag0 == flag1;
}

bool isLegal(int indr, int ind0, int ind1, int indl, const std::vector<Vector2f>& pointSet) {
    if(ind0 <= 0 && ind1 <= 0) return true;
    // is convex quadrilateral
    bool flag0, flag1;
    flag0 = isLeft(ind0, indr, indl, pointSet);
    flag1 = isLeft(ind1, indr, indl, pointSet);
    std::cout << "flag0 = " << flag0 << std::endl;
    std::cout << "flag1 = " << flag1 << std::endl;
    if(flag0 == flag1) return true;

    if(indr < 0 || ind0 < 0 || ind1 < 0 || indl < 0) {
        if(indr >= 0 && indl >= 0)  return false;
        else return true;
        if(ind0 >= 0 && ind1 >= 0)  return true;
    }

    Vector2f pr = pointSet[indr], p0 = pointSet[ind0], p1 = pointSet[ind1], pl = pointSet[indl];
    float angleCosine0 = dotProduct(p0 - pr, p1 - pr) / ((p0 - pr).norm() * (p1 - pr).norm());
    float angleCosine1 = dotProduct(p0 - pl, p1 - pl) / ((p0 - pl).norm() * (p1 - pl).norm());
    if(-angleCosine0 > angleCosine1) return false;
    return true;
}

inline void TriangleList::legalizeEdge(const int indr, const int ind0, const int ind1, const std::vector<Vector2f>& pointSet) {
    if(edgeTable[ind0 + 2][ind1 + 2].size() < 2) return;
    ListNode *ptr0 = edgeTable[ind0 + 2][ind1 + 2][0], *ptr1 = edgeTable[ind0 + 2][ind1 + 2][1];
    int indl;
    if(indr != ptr0->tri_v0 && indr != ptr0->tri_v1 && indr != ptr0->tri_v2)
        std::swap(ptr0, ptr1); // indr is in ptr0->tri
    if(ptr1->tri_v0 != ind0 && ptr1->tri_v0 != ind1)    indl = ptr1->tri_v0;
    else if(ptr1->tri_v1 != ind0 && ptr1->tri_v1 != ind1)    indl = ptr1->tri_v1;
    else    indl = ptr1->tri_v2;
    //return ;
    std::cout << "is here？" << std::endl;
    if(isLegal(indr, ind0, ind1, indl, pointSet)) return;
    std::cout << "no" << std::endl;

    std::cout << "indr = " << indr << ", ind0 = " << ind0 << ", ind1 = " << ind1 << ", indl = " << indl << std::endl;
    std::cout << "ptr0 = " << ptr0->tri_v0 << " " << ptr0->tri_v1 << " " << ptr0->tri_v2 << std::endl;
    std::cout << "ptr1 = " << ptr1->tri_v0 << " " << ptr1->tri_v1 << " " << ptr1->tri_v2 << std::endl;
//    return ;

    TreeNode *current_treenode0 = ptr0->treenode, *current_treenode1 = ptr1->treenode;
    ListNode *new_listnode0, *new_listnode1;
    TreeNode *new_treenode0, *new_treenode1;
    if(isLeft(ind1, indr, indl, pointSet)) {
        new_listnode0 = new ListNode(indr, indl, ind1);
        new_listnode1 = new ListNode(indl, indr, ind0);
        new_treenode0 = new TreeNode(indr, indl, ind1);
        new_treenode1 = new TreeNode(indl, indr, ind0);
    }
    else {
        new_listnode0 = new ListNode(indr, indl, ind0);
        new_listnode1 = new ListNode(indl, indr, ind1);
        new_treenode0 = new TreeNode(indr, indl, ind0);
        new_treenode1 = new TreeNode(indl, indr, ind1);
    }
    std::cout << "HERE____________" << std::endl;
    crossLink(new_listnode0, new_treenode0);
    crossLink(new_listnode1, new_treenode1);
    linkEdge(new_listnode0);
    linkEdge(new_listnode1);
    current_treenode0->childNum = 2, current_treenode1->childNum = 2;
    current_treenode0->child0 = new_treenode0, current_treenode0->child1 = new_treenode1;
    current_treenode1->child0 = new_treenode0, current_treenode1->child1 = new_treenode1;

    if(ptr0->pre == nullptr)
        head = new_listnode0;
    else {
        ptr0->pre->next = new_listnode0;
        new_listnode0->pre = ptr0->pre;
    }
    if(ptr1->pre == nullptr)
        head = new_listnode1;
    else {
        ptr1->pre->next = new_listnode1;
        new_listnode1->pre = ptr1->pre;
    }
    new_listnode0->next = ptr0->next;
    if(new_listnode0->next != nullptr)
        new_listnode0->next->pre = new_listnode0;
    new_listnode1->next = ptr1->next;
    if(new_listnode1->next != nullptr)
        new_listnode1->next->pre = new_listnode1;
    unlinkEdge(ptr0);
    unlinkEdge(ptr1);
    ListNode* ptr = head;
    std::cout << "display list :" << std::endl;
    while(ptr != nullptr) {
        std::cout << ptr->tri_v0 << ", " << ptr->tri_v1 << ", " << ptr->tri_v2 << std::endl;
        ptr = ptr->next;
    }
    delete ptr0;
    delete ptr1;
    legalizeEdge(indr, ind0, indl, pointSet);
    legalizeEdge(indr, ind1, indl, pointSet);
}

void TriangleList::addPoint(const std::vector<Vector2f>& pointSet, const int& index, TriangleTree& tree, TriangleList& L){
    Vector2f point = pointSet[index];
    std::vector<ListNode*> ptrVec;
    findTriangle(index, tree.root, ptrVec, pointSet);
    if(ptrVec.size() == 1) {
        ListNode* ptr = ptrVec[0];
        int ind0 = ptr->tri_v0, ind1 = ptr->tri_v1, ind2 = ptr->tri_v2;
        TreeNode *current_treenode = ptr->treenode;
        ListNode *new_listnode0 = new ListNode(index, ind0, ind1);
        ListNode *new_listnode1 = new ListNode(index, ind1, ind2);
        ListNode *new_listnode2 = new ListNode(index, ind2, ind0);
        TreeNode *new_treenode0 = new TreeNode(index, ind0, ind1);
        TreeNode *new_treenode1 = new TreeNode(index, ind1, ind2);
        TreeNode *new_treenode2 = new TreeNode(index, ind2, ind0);
        linkEdge(new_listnode0);
        linkEdge(new_listnode1);
        linkEdge(new_listnode2);
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
        std::cout << "add new point" << std::endl;
        //printEdgeTable();
        unlinkEdge(ptr);
        delete ptr;
        std::cout << "remove old edge" << std::endl;
        //printEdgeTable();
        legalizeEdge(index, ind0, ind1, pointSet);
        legalizeEdge(index, ind1, ind2, pointSet);
        legalizeEdge(index, ind2, ind0, pointSet);
        //std::cout << "legalize" << std::endl;
        //printEdgeTable();
    }
    else if(ptrVec.size() == 2) {
        ListNode *ptr0 = ptrVec[0], *ptr1 = ptrVec[1];
        int ind00 = ptr0->tri_v0, ind01 = ptr0->tri_v1, ind02 = ptr0->tri_v2;
        int ind10 = ptr1->tri_v0, ind11 = ptr1->tri_v1, ind12 = ptr1->tri_v2;
        std::vector<int> tmpInd0; // points that are used twice
        std::vector<int> tmpInd1; // points that are used once
        if(ind00 == ind10 || ind00 == ind11 || ind00 == ind12)  tmpInd0.push_back(ind00);
        else tmpInd1.push_back(ind00);
        if(ind01 == ind10 || ind01 == ind11 || ind01 == ind12)  tmpInd0.push_back(ind01);
        else tmpInd1.push_back(ind01);
        if(ind02 == ind10 || ind02 == ind11 || ind02 == ind12)  tmpInd0.push_back(ind02);
        else tmpInd1.push_back(ind02);
        if(tmpInd1[0] == ind01)
            std::swap(tmpInd0[0], tmpInd0[1]);
        if(ind10 != ind00 && ind10 != ind01 && ind10 != ind02)  tmpInd1.push_back(ind10);
        else if(ind11 != ind00 && ind11 != ind01 && ind11 != ind02)  tmpInd1.push_back(ind11);
        else tmpInd1.push_back(ind12);
        TreeNode *current_treenode0 = ptr0->treenode, *current_treenode1 = ptr1->treenode;
        ListNode *new_listnode00 = new ListNode(index, tmpInd1[0], tmpInd0[0]);
        ListNode *new_listnode01 = new ListNode(index, tmpInd0[1], tmpInd1[0]);
        new_listnode00->next = new_listnode01;
        new_listnode01->pre = new_listnode00;
        ListNode *new_listnode10 = new ListNode(index, tmpInd0[0], tmpInd1[1]);
        ListNode *new_listnode11 = new ListNode(index, tmpInd1[1], tmpInd0[1]);
        new_listnode10->next = new_listnode11;
        new_listnode11->pre = new_listnode10;
        TreeNode *new_treenode00 = new TreeNode(index, tmpInd1[0], tmpInd0[0]);
        TreeNode *new_treenode01 = new TreeNode(index, tmpInd0[1], tmpInd1[0]);
        TreeNode *new_treenode10 = new TreeNode(index, tmpInd0[0], tmpInd1[1]);
        TreeNode *new_treenode11 = new TreeNode(index, tmpInd1[1], tmpInd0[1]);
        linkEdge(new_listnode00);
        linkEdge(new_listnode01);
        linkEdge(new_listnode10);
        linkEdge(new_listnode11);
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
        unlinkEdge(ptr0);
        unlinkEdge(ptr1);
        delete ptr0;
        delete ptr1;
        legalizeEdge(index, tmpInd0[0], tmpInd1[0], pointSet);
        legalizeEdge(index, tmpInd0[0], tmpInd1[1], pointSet);
        legalizeEdge(index, tmpInd0[1], tmpInd1[0], pointSet);
        legalizeEdge(index, tmpInd0[1], tmpInd1[1], pointSet);
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

void TriangleList::triangulation(std::vector<Vector2f>& pointSet) {
    //if(pointSet.size() < 3) return;

    edgeTable = std::vector<std::vector<std::vector<ListNode*>>>(pointSet.size() + 2, std::vector<std::vector<ListNode*>>(pointSet.size() + 2, std::vector<ListNode*>(0)));
    // select highest point and shuffle point set.    
    for(int i = 1; i < pointSet.size(); i++) {
        if((pointSet[i].y > pointSet[0].y) || (pointSet[i].y == pointSet[0].y && pointSet[i].x > pointSet[0].x))
            std::swap(pointSet[i], pointSet[0]);
    }
    // shuffle(pointSet);
    // construct bounding triangle
    head = new ListNode(-2, -1, 0);

    TriangleTree tree;
    tree.root = new TreeNode(-2, -1, 0);
    linkEdge(head);
    crossLink(head, tree.root);

    // add every point from point set
    for(int i = 1; i < pointSet.size(); i++) {
        std::cout << "add point " << i << ": " << pointSet[i] << std::endl;
        addPoint(pointSet, i, tree, *this);
    }
    pointSet.push_back(Vector2f(100, 990));
    pointSet.push_back(Vector2f(990, 10));
    
    ListNode* ptr = head;
    std::cout << "display list :" << std::endl;
    while(ptr != nullptr) {
        std::cout << ptr->tri_v0 << ", " << ptr->tri_v1 << ", " << ptr->tri_v2 << std::endl;
        ptr = ptr->next;
    }

    // remove bounding triangle
    /*
    while(ptr != nullptr) {
        if(ptr->tri_v0 < 0 || ptr->tri_v1 < 0 || ptr->tri_v2 < 0) {
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
    printEdgeTable();
    ptr = head;
    while(ptr != nullptr) {
        if(ptr->tri_v0 < 0 || ptr->tri_v1 < 0 || ptr->tri_v2 < 0) {
            if(ptr->tri_v0 == -1)
                ptr->tri_v0 = pointSet.size() - 1;
            else if(ptr->tri_v0 == -2)
                ptr->tri_v0 = pointSet.size() - 2;
            if(ptr->tri_v1 == -1)
                ptr->tri_v1 = pointSet.size() - 1;
            else if(ptr->tri_v1 == -2)
                ptr->tri_v1 = pointSet.size() - 2;
            if(ptr->tri_v2 == -1)
                ptr->tri_v2 = pointSet.size() - 1;
            else if(ptr->tri_v2 == -2)
                ptr->tri_v2 = pointSet.size() - 2;

        }
        ptr = ptr->next;
    }
    //*/
}

void TriangleList::drawTriangulation(const std::vector<Vector2f>& pointSet, Screen& scn) {
    ListNode* ptr = head;
    int i = 0;
    while(ptr != nullptr) {
        std::cout << "ptr: " << ptr->tri_v0 << ", " << ptr->tri_v1 << ", " << ptr->tri_v2 << std::endl;
        Triangle tri(pointSet[ptr->tri_v0], pointSet[ptr->tri_v1], pointSet[ptr->tri_v2]);
//        std::cout << "tri: " << tri.v0 << ", " << tri.v1 << ", " << tri.v2 << std::endl;
        drawTriangle(tri, scn);
        ptr = ptr->next;
//        std::string a = "test";
//        char p = '0' + i;
//        a += p;
//        a += ".png";
//        scn.imageWrite(a);
//        i++;
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