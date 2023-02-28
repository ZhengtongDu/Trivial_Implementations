#ifndef DELAUNAYTRIANGULATION_H
#define DELAUNAYTRIANGULATION_H

#include "Triangle.h"
#include "Draw.h"
#include <utility>

struct TreeNode;
struct ListNode;

struct TreeNode{
    int tri_v0, tri_v1, tri_v2;
    std::shared_ptr<TreeNode> child0, child1, child2;
    int childNum;
    std::shared_ptr<ListNode> listnode;
    TreeNode(int _v0, int _v1, int _v2)
    : tri_v0(_v0), tri_v1(_v1), tri_v2(_v2), child0(nullptr), child1(nullptr), child2(nullptr), childNum(0) { }
};

struct ListNode{
    int tri_v0, tri_v1, tri_v2;
    std::shared_ptr<ListNode> pre, next;
    std::shared_ptr<TreeNode> treenode;
    ListNode(int _v0, int _v1, int _v2)
    : tri_v0(_v0), tri_v1(_v1), tri_v2(_v2), pre(nullptr), next(nullptr) { }
};

class TriangleTree
{
public:
    TriangleTree() {}
    ~TriangleTree() {}
public:
    std::shared_ptr<TreeNode> root;
};

class TriangleList
{
public:
    void addPoint(const std::vector<Vector2f>&, const int&, TriangleTree&);
    void triangulation(std::vector<Vector2f>&);
    void drawTriangulation(const std::vector<Vector2f>& pointSet, Screen& scn);
    void linkEdge(std::shared_ptr<ListNode>);
    void unlinkEdge(const int, const int, std::shared_ptr<ListNode>);
    void unlinkEdge(std::shared_ptr<ListNode> ptr);
    void legalizeEdge(const int, const int, const int, const std::vector<Vector2f>&);
    void printEdgeTable();
    std::shared_ptr<ListNode> head;
    std::vector<std::vector<std::vector<std::shared_ptr<ListNode>>>> edgeTable;
};

/////
// End Class Declaration
/////

/////
// Function Definition
/////

void crossLink(std::shared_ptr<ListNode> lnode, std::shared_ptr<TreeNode> tnode) {
    lnode->treenode = tnode;
    tnode->listnode = lnode;
}

void TriangleList::linkEdge(std::shared_ptr<ListNode> ptr) {
    int ind0 = ptr->tri_v0 + 2, ind1 = ptr->tri_v1 + 2, ind2 = ptr->tri_v2 + 2;
    edgeTable[ind0][ind1].push_back(ptr);
    edgeTable[ind1][ind0].push_back(ptr);
    edgeTable[ind0][ind2].push_back(ptr);
    edgeTable[ind2][ind0].push_back(ptr);
    edgeTable[ind1][ind2].push_back(ptr);
    edgeTable[ind2][ind1].push_back(ptr);
}

void TriangleList::unlinkEdge(const int ind0, const int ind1, std::shared_ptr<ListNode> ptr) {
    int i = 0;
    for(;i < edgeTable[ind0 + 2][ind1 + 2].size(); i++)
        if(edgeTable[ind0 + 2][ind1 + 2][i] == ptr) break;
    edgeTable[ind0 + 2][ind1 + 2].erase(edgeTable[ind0 + 2][ind1 + 2].begin() + i);
    edgeTable[ind1 + 2][ind0 + 2].erase(edgeTable[ind1 + 2][ind0 + 2].begin() + i);
}

void TriangleList::unlinkEdge(std::shared_ptr<ListNode> ptr) {
    unlinkEdge(ptr->tri_v0, ptr->tri_v1, ptr);
    unlinkEdge(ptr->tri_v1, ptr->tri_v2, ptr);
    unlinkEdge(ptr->tri_v2, ptr->tri_v0, ptr);
}

void printTree(std::shared_ptr<TreeNode> ptr) {
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
        if(ind1 < 0 && ind2 < 0) return true; // point lies in the left of edge(v1, v2);  
        if(ind1 == -1) {
            if((v2.y > point.y) || (v2.y == point.y && v2.x > point.x))
                return true;
        }
        if(ind2 == -1) {
            if((v1.y < point.y) || (v1.y == point.y && v1.x < point.x))
                return true;
        }
        if(ind1 == -2) {
            if((v2.y < point.y) || (v2.y == point.y && v2.x < point.x))
                return true;
        }
        if(ind2 == -2) {
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

void findTriangle(const int indr, const std::shared_ptr<TreeNode> ptr, std::vector<std::shared_ptr<ListNode>>& ptrVec, const std::vector<Vector2f>& pointSet) {
    if(ptr == nullptr)  return;
    if(inTriangle(indr, ptr->tri_v0, ptr->tri_v1, ptr->tri_v2, pointSet)) {
        if(ptr->child0 == nullptr) {
            for(int i = 0; i < ptrVec.size(); i++)
                if(ptrVec[i] == ptr->listnode)    return;
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
    std::shared_ptr<ListNode> ptr0 = edgeTable[ind0 + 2][ind1 + 2][0], ptr1 = edgeTable[ind0 + 2][ind1 + 2][1];
    int indl;
    if(indr != ptr0->tri_v0 && indr != ptr0->tri_v1 && indr != ptr0->tri_v2)
        std::swap(ptr0, ptr1); // indr is in ptr0->tri
    if(ptr1->tri_v0 != ind0 && ptr1->tri_v0 != ind1)    indl = ptr1->tri_v0;
    else if(ptr1->tri_v1 != ind0 && ptr1->tri_v1 != ind1)    indl = ptr1->tri_v1;
    else    indl = ptr1->tri_v2;
    if(isLegal(indr, ind0, ind1, indl, pointSet)) return;

    std::shared_ptr<TreeNode> current_treenode0 = ptr0->treenode, current_treenode1 = ptr1->treenode;
    std::shared_ptr<ListNode> new_listnode0, new_listnode1;
    std::shared_ptr<TreeNode> new_treenode0, new_treenode1;
    if(isLeft(ind1, indr, indl, pointSet)) {
        new_listnode0.reset(new ListNode(indr, indl, ind1));
        new_listnode1.reset(new ListNode(indl, indr, ind0));
        new_treenode0.reset(new TreeNode(indr, indl, ind1));
        new_treenode1.reset(new TreeNode(indl, indr, ind0));
    }
    else {
        new_listnode0.reset(new ListNode(indr, indl, ind0));
        new_listnode1.reset(new ListNode(indl, indr, ind1));
        new_treenode0.reset(new TreeNode(indr, indl, ind0));
        new_treenode1.reset(new TreeNode(indl, indr, ind1));
    }
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
    std::shared_ptr<ListNode> ptr = head;
    ptr0.reset();
    ptr1.reset();
    legalizeEdge(indr, ind0, indl, pointSet);
    legalizeEdge(indr, ind1, indl, pointSet);
}

void TriangleList::addPoint(const std::vector<Vector2f>& pointSet, const int& index, TriangleTree& tree){
    Vector2f point = pointSet[index];
    std::vector<std::shared_ptr<ListNode>> ptrVec;
    findTriangle(index, tree.root, ptrVec, pointSet);
    if(ptrVec.size() == 1) {
        std::shared_ptr<ListNode> ptr = ptrVec[0];
        int ind0 = ptr->tri_v0, ind1 = ptr->tri_v1, ind2 = ptr->tri_v2;
        std::shared_ptr<TreeNode> current_treenode = ptr->treenode;
        std::shared_ptr<ListNode> new_listnode0(new ListNode(index, ind0, ind1));
        std::shared_ptr<ListNode> new_listnode1(new ListNode(index, ind1, ind2));
        std::shared_ptr<ListNode> new_listnode2(new ListNode(index, ind2, ind0));
        std::shared_ptr<TreeNode> new_treenode0(new TreeNode(index, ind0, ind1));
        std::shared_ptr<TreeNode> new_treenode1(new TreeNode(index, ind1, ind2));
        std::shared_ptr<TreeNode> new_treenode2(new TreeNode(index, ind2, ind0));
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
            head = new_listnode0;
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
        unlinkEdge(ptr);
        ptr.reset();
        legalizeEdge(index, ind0, ind1, pointSet);
        legalizeEdge(index, ind1, ind2, pointSet);
        legalizeEdge(index, ind2, ind0, pointSet);
    }
    else if(ptrVec.size() == 2) {
        std::shared_ptr<ListNode> ptr0 = ptrVec[0], ptr1 = ptrVec[1];
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
        std::shared_ptr<TreeNode> current_treenode0 = ptr0->treenode, current_treenode1 = ptr1->treenode;
        std::shared_ptr<ListNode> new_listnode00(new ListNode(index, tmpInd1[0], tmpInd0[0]));
        std::shared_ptr<ListNode> new_listnode01(new ListNode(index, tmpInd0[1], tmpInd1[0]));
        new_listnode00->next = new_listnode01;
        new_listnode01->pre = new_listnode00;
        std::shared_ptr<ListNode> new_listnode10(new ListNode(index, tmpInd0[0], tmpInd1[1]));
        std::shared_ptr<ListNode> new_listnode11(new ListNode(index, tmpInd1[1], tmpInd0[1]));
        new_listnode10->next = new_listnode11;
        new_listnode11->pre = new_listnode10;
        std::shared_ptr<TreeNode> new_treenode00(new TreeNode(index, tmpInd1[0], tmpInd0[0]));
        std::shared_ptr<TreeNode> new_treenode01(new TreeNode(index, tmpInd0[1], tmpInd1[0]));
        std::shared_ptr<TreeNode> new_treenode10(new TreeNode(index, tmpInd0[0], tmpInd1[1]));
        std::shared_ptr<TreeNode> new_treenode11(new TreeNode(index, tmpInd1[1], tmpInd0[1]));
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
            head = new_listnode00;
        else {
            ptr0->pre->next = new_listnode00;
            new_listnode00->pre = ptr0->pre;
        }
        if(ptr1->pre == nullptr)
            head = new_listnode10;
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
        ptr0.reset();
        ptr1.reset();
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
    if(pointSet.size() < 3) return;

    edgeTable = std::vector<std::vector<std::vector<std::shared_ptr<ListNode>>>>(pointSet.size() + 2, std::vector<std::vector<std::shared_ptr<ListNode>>>(pointSet.size() + 2, std::vector<std::shared_ptr<ListNode>>(0)));
    // select highest point and shuffle point set.    
    for(int i = 1; i < pointSet.size(); i++) {
        if((pointSet[i].y > pointSet[0].y) || (pointSet[i].y == pointSet[0].y && pointSet[i].x > pointSet[0].x))
            std::swap(pointSet[i], pointSet[0]);
    }
    shuffle(pointSet);
    // construct bounding triangle
    head.reset(new ListNode(-2, -1, 0));

    TriangleTree tree;
    tree.root.reset(new TreeNode(-2, -1, 0));
    linkEdge(head);
    crossLink(head, tree.root);

    // add every point from point set
    for(int i = 1; i < pointSet.size(); i++) {
        std::cout << "add point " << i << ": " << pointSet[i] << std::endl;
        addPoint(pointSet, i, tree);
    }
    std::shared_ptr<ListNode> ptr = head;

    // remove bounding triangle
    ///*
    while(ptr != nullptr) {
        if(ptr->tri_v0 < 0 || ptr->tri_v1 < 0 || ptr->tri_v2 < 0) {
            if(ptr == head) {
                head = head->next;
                head->pre = nullptr;
                ptr.reset();
                ptr = head;
            }
            else {
                std::shared_ptr<ListNode> tmp = ptr->next;
                ptr->pre->next = ptr->next;
                if(ptr->next != nullptr)
                    ptr->next->pre = ptr->pre;
                ptr.reset();
                ptr = tmp;
            }
        }
        else
            ptr = ptr->next;
    }
    //*/
    // show bounding triangle
    /*
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
    */
}

void TriangleList::drawTriangulation(const std::vector<Vector2f>& pointSet, Screen& scn) {
    std::shared_ptr<ListNode> ptr = head;
    int i = 0;
    while(ptr != nullptr) {
        Triangle tri(pointSet[ptr->tri_v0], pointSet[ptr->tri_v1], pointSet[ptr->tri_v2]);
        drawTriangle(tri, scn);
        ptr = ptr->next;
    }
}
#endif // DELAUNAYTRIANGULATION_H