#ifndef VORONOIDIAGRAM_H
#define VORONOIDIAGRAM_H

#include <iostream>
#include <queue>
#include "Draw.h"
#include "Vector.h"

enum eventType {siteEvent, circleEvent};
enum tnodeType {tupleNode, pointNode};

struct eventNode{
public:
    eventNode(Vector2f _pos, eventType t)
        : pos(_pos), eNodeType(t) { }
    eventNode() {}
    ~eventNode() {}
    eventNode(const eventNode& other) {
        pos = other.pos;
        eNodeType = other.eNodeType;
    }
    eventNode& operator=(const eventNode& other) {
        if(&other == this)
            return *this;
        pos = other.pos;
        eNodeType = other.eNodeType;
        return *this;
    }

    bool operator < (const eventNode& b) const {
        return pos.y < b.pos.y || (pos.y == b.pos.y && pos.x < b.pos.x);
    }

    bool operator > (const eventNode& b) const {
        return pos.y > b.pos.y || (pos.y == b.pos.y && pos.x > b.pos.x);
    }

    Vector2f pos;
    eventType eNodeType;
};

struct listNode {
public:
    std::shared_ptr<listNode> next, pre;
    Vector2f start, end;
};

struct treeNode {
public:
    std::shared_ptr<treeNode> left, right, parent;
    tnodeType type;

    // tupleNode elements
    std::vector<Vector2f> tuple;

    // pointNode elements
    Vector2f point;
    bool containCirclePoint;
    Vector2f circlePoint;

    treeNode() : left(nullptr), right(nullptr), parent(nullptr), containCirclePoint(false), circlePoint() {
        type = pointNode;
        point = Vector2f();
        tuple = std::vector<Vector2f>();
    }
    
    treeNode(const std::vector<Vector2f>& _tuple) : left(nullptr), right(nullptr), parent(nullptr), containCirclePoint(false), circlePoint() {
        type = tupleNode;
        tuple = std::vector<Vector2f>(2);
        tuple[0] = _tuple[0];
        tuple[1] = _tuple[1];
    }
    
    treeNode(const Vector2f& _point) : left(nullptr), right(nullptr), parent(nullptr), containCirclePoint(false), circlePoint() {
        type = pointNode;
        point = _point;
    }
};

class tree {
public:
    tree() : root(nullptr){}
    void insertNode(const Vector2f&);
    void deleteNode();
    bool empty() {
        return root == nullptr;
    }
    private:
    std::shared_ptr<treeNode> root;
};

void tree::insertNode(const Vector2f& _point) {
    if(root == nullptr)
        root = std::make_shared<treeNode>(_point);
    std::shared_ptr<treeNode> ptr = root;
    while(ptr->type == tupleNode) {
        if(_point.x < ptr->tuple[0].x)
            ptr = ptr->left;
        else if(_point.x > ptr->tuple[1].x)
            ptr = ptr->right;
        else break;
    }
    std::vector<Vector2f> newTuple(2);
    std::shared_ptr<treeNode> newPointPtr = std::make_shared<treeNode>(_point), newTuplePtr = std::make_shared<treeNode>(newTuple);
        if(ptr->type == pointNode) {
        std::shared_ptr<treeNode> parentPtr = ptr->parent;
        if(parentPtr->left == ptr)
            parentPtr->left = newTuplePtr;
        else
            parentPtr->right = newTuplePtr;
        newTuplePtr->parent = parentPtr;

        if(ptr->point.x > newPointPtr->point.x) {
            newTuplePtr->tuple[0] = newPointPtr->point;
            newTuplePtr->tuple[1] = ptr->point;
            newTuplePtr->left = newPointPtr;
            newTuplePtr->right = ptr;
        }
        else { // ptr->point.x <= newPointPtr->point.x
            newTuplePtr->tuple[0] = ptr->point;
            newTuplePtr->tuple[1] = newPointPtr->point;
            newTuplePtr->left = ptr;
            newTuplePtr->right = newPointPtr;
        }
        ptr->parent = newTuplePtr;
        newPointPtr->parent = newTuplePtr;
    }
    else { // ptr->type == tupleNode
        newTuplePtr->right = ptr->right;
        newTuplePtr->right->parent = newTuplePtr;
        newTuplePtr->left = newPointPtr;
        newPointPtr->parent = newTuplePtr;
        newTuplePtr->tuple[0] = _point;
        newTuplePtr->tuple[1] = ptr->tuple[1];
        ptr->right = newTuplePtr;
        newTuplePtr->parent = ptr;
        ptr->tuple[1] = _point;
    }
}

class voronoiDiagram {
    void handleSiteEvent(const eventNode&);
    void handleCircleEvent(const eventNode&);
    void solve();
    void draw();
    std::vector<Vector2f> pointSet;
    // but it doesn't have a delete function
    // unfinished
    std::priority_queue<eventNode> eventQueue;
    tree stateTree;
    struct edgeList
    {
        edgeList(std::shared_ptr<listNode>& node) : head(node), tail(node) { }
        std::shared_ptr<listNode> head, tail;
        // unfinished
        void insert(std::shared_ptr<listNode>& node) {
        }
    };
};

// unfinished
void voronoiDiagram::handleSiteEvent(const eventNode& curNode) {
    if(stateTree.empty()){
        stateTree.insertNode(curNode.pos);
    }
    else {
        // deal with the false alarm
        // replace the arc \alpha with a three-leaves subtree
        // create new half-edge record 
        // check if the triple arcs converge
    }
}

void voronoiDiagram::handleCircleEvent(const eventNode& curNode) {
    // delete leave \gamma and update tuples delete events involving \alpha
    // add the center of the circle
    // check if the new triple arcs converge
}

void voronoiDiagram::solve() {
    while(!eventQueue.empty())
        eventQueue.pop();
    for(int i = 0; i < pointSet.size(); i++)
        eventQueue.emplace(eventNode(pointSet[i], siteEvent));
    eventNode current;
    while(!eventQueue.empty()){
        current = eventQueue.top();
        eventQueue.pop();
        // deal with the event
        // unfinished
        if(current.eNodeType == siteEvent) {
            handleSiteEvent(current);
        }
        else { // current.eNodeType == circleEvent 
            handleCircleEvent(current);
        }
    }
    // deal with the redundant elements in the tree
    // unfinished
    draw();
}

// unfinished
void voronoiDiagram::draw() {

}

#endif // VORONOIDIAGRAM_H