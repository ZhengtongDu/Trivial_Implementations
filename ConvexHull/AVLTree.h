#ifndef AVLTREE_H
#define AVLTREE_H
#include<iostream>

template <typename T>
class AVLTree{
public:

  AVLTree() : root(nullptr) { }
  AVLTree( const AVLTree &rhs) : root(nullptr)
  {
    root = clone( rhs.root );
  }
  ~AVLTree()
  {
    delete_subtree(root);
  }

  struct AVLNode{
    T value;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;
    int height;
    int skew;
    AVLNode(const T & _v, AVLNode *_p = nullptr, AVLNode *_l = nullptr, AVLNode *_r = nullptr, int _h = 0, int _s = 0) : value(_v), parent(_p), left(_l), right(_r), height(_h), skew(_s){
      int lh = -1; 
      int rh = -1;
      if(_l != nullptr) lh = _l->height;
      if(_r != nullptr) rh = _r->height;
      height = std::max(lh, rh) + 1;
      skew = lh - rh;
    }
  };

  void insert(const T& _v);
  bool find(const T& _v);
  void pop(const T& _v);
  T pop_max();
  T pop_min();
  void print();
  
private:
  AVLNode *clone(AVLNode *t) const
  {
    if(t == nullptr)
      return nullptr;
    else
      return new AVLNode(t->value, clone( t->left ), clone(t->right ), t->height, t->skew);
  }
  AVLNode *find_pos(const T&);
  AVLNode *precessor(const AVLNode *);
  AVLNode *successor(const AVLNode *);
  void delete_subtree(AVLNode *);
  void left_rotate(AVLNode *);
  void right_rotate(AVLNode *);
  void maintain_node(AVLNode *);
  void print_subtree(AVLNode *);
  
public:
  AVLNode *root;
  
};

///////////////////////////////
/// public member functions ///
///////////////////////////////

template<typename T>
void AVLTree<T>::insert(const T& _v)
{
  if(root == nullptr) root = new AVLNode(_v);
  else{
    AVLNode* ptr = root;
    AVLNode* pptr = ptr;
    while(pptr != nullptr){
      ptr = pptr;
      if(ptr->value == _v){
        std::cout << "Already inserted same value." << std::endl;
        return;
      }
      if(ptr->value > _v)
        pptr = ptr->left;
      else
        pptr = ptr->right;
    }
    if(ptr->value > _v){
      ptr->left = new AVLNode(_v);
      ptr->left->parent = ptr;
    }
    else{
      ptr->right = new AVLNode(_v);
      ptr->right->parent = ptr;
    }
    maintain_node(ptr);
  }
}

template<typename T>
bool AVLTree<T>::find(const T& _v){
  if(find_pos(_v) == nullptr)
    return false;
  else
    return true;
}

template<typename T>
void AVLTree<T>::pop(const T& _v){
  std::cout << "check point, value is " << _v << std::endl;
  if(!find(_v)){std::cerr << "Cannot pop due to no existing." << std::endl; return;}
  AVLNode *ptr = find_pos(_v);
  AVLNode *pptr = precessor(ptr);
  AVLNode *tr;
  if(pptr != nullptr){
  std::cout << "case1" << std::endl;
    ptr->value = pptr->value;
    tr = pptr->parent;
    if(pptr == tr->left) tr->left = nullptr;
    else tr->right = nullptr;
    delete pptr;
  }
  else{
  std::cout << "case2" << std::endl;
    pptr = successor(ptr);
    if(pptr != nullptr){
      ptr->value = pptr->value;
      tr = pptr->parent;
      if(pptr == tr->left) tr->left = nullptr;
      else tr->right = nullptr;
      delete pptr;
    }
    else{
  std::cout << "case3" << std::endl;
      tr = ptr->parent;
      if(ptr == tr->left) tr->left = nullptr;
      else tr->right = nullptr;
      delete ptr;
    }
  }
  std::cout << "Successfully popping!" << std::endl;
  std::cout << "check point 2, parent's value is " << tr->value << std::endl;
  if(tr != nullptr) maintain_node(tr);
}

template<typename T>
T AVLTree<T>::pop_max(){
  if(root == nullptr) std::cerr << "Empty tree." << std::endl;
  AVLNode *ptr = root;
  while(ptr->right != nullptr)
    ptr = ptr->right;
  T ret = ptr->value;
  pop(ptr);
}

template<typename T>
T AVLTree<T>::pop_min(){
  if(root == nullptr) std::cerr << "Empty tree." << std::endl;
  AVLNode *ptr = root;
  while(ptr->left != nullptr)
    ptr = ptr->left;
  T ret = ptr->value;
  pop(ptr);
}

template<typename T>
void AVLTree<T>::print()
{
  print_subtree(root);
}

////////////////////////////////
/// private member functions ///
////////////////////////////////

template<typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::find_pos(const T& _v){
  AVLNode *ptr = root;
  while(ptr != nullptr){
    if(ptr->value == _v)
      return ptr;
    if(ptr->value > _v)
      ptr = ptr->left;
    else
      ptr = ptr->right;
  }
  std::cout << "Not found." << std::endl;
  return nullptr;
}

// Get the precessor in the left subtree of ptr
template<typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::precessor(const AVLNode *ptr){ 
  if(ptr == nullptr) std::cerr << "No precessor of nullptr." << std::endl;
  AVLNode *pptr = ptr->left;
  if(pptr == nullptr) return nullptr;
  while(pptr->right != nullptr)
    pptr = pptr->right;
  return pptr;
}

// Get the successor in the right subtree of ptr
template<typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::successor(const AVLNode *ptr){
  if(ptr == nullptr) std::cerr << "No successor of nullptr." << std::endl;
  AVLNode *pptr = ptr->right;
  if(pptr == nullptr) return nullptr;
  while(pptr->left != nullptr)
    pptr = pptr->left;
  return pptr;
}

template<typename T>
void AVLTree<T>::delete_subtree(AVLNode *ptr){
  if(ptr != nullptr){
    delete_subtree(ptr->left);
    delete_subtree(ptr->right);
    delete ptr;
  }
  ptr = nullptr;
}

template<typename T>
void AVLTree<T>::left_rotate(AVLNode *ptr){
  if(ptr==nullptr) std::cerr << "Empty node.";
  if(ptr->right==nullptr) std::cerr << "Empty node.";
  AVLNode *p = ptr->parent;
  if(p == nullptr){ // solve the situation when ptr is root
    root = ptr->right;
    ptr->right = root->left;
    root->left = ptr;
    maintain_node(root->left);
    maintain_node(root);
  }
  else{
    if(p->left == ptr){
      p->left = ptr->right;
      ptr->right = p->left->left;
      p->left->left = ptr;
      maintain_node(p->left->left);
      maintain_node(p->left);
    }
    else{
      p->right = ptr->right;
      ptr->right = p->right->left;
      p->right->left = ptr;
      maintain_node(p->right->left);
      maintain_node(p->right);
    }
  }
}

template<typename T>
void AVLTree<T>::right_rotate(AVLNode *ptr){
  if(ptr==nullptr) std::cerr << "Empty node.";
  if(ptr->left==nullptr) std::cerr << "Empty node.";
  AVLNode *p = ptr->parent;
  if(p == nullptr){ // solve the situation when ptr is root
    root = ptr->left;
    ptr->left = root->right;
    root->right = ptr;
    maintain_node(root->right);
    maintain_node(root);
  }
  else{
    if(p->left == ptr){
      p->left = ptr->left;
      ptr->left = p->left->right;
      p->left->right = ptr;
      maintain_node(p->left->right);
      maintain_node(p->left);
    }
    else{
      p->right = ptr->left;
      ptr->left = p->right->right;
      p->right->right = ptr;
      maintain_node(p->right->right);
      maintain_node(p->right);
    }
  }
}

template<typename T>
void AVLTree<T>::maintain_node(AVLNode *ptr)
{
  if(ptr == nullptr);
  else{
    AVLNode *_l = ptr->left;
    AVLNode *_r = ptr->right;
    int lh = -1;
    int rh = -1;
    if(_l != nullptr) lh = _l->height;
    if(_r != nullptr) rh = _r->height;
    ptr->height = std::max(lh, rh) + 1;
    ptr->skew = lh - rh;
    if(ptr->skew == 2) right_rotate(ptr);
    else if(ptr->skew == -2) left_rotate(ptr);
    maintain_node(ptr->parent);
  }
}

template<typename T>
void AVLTree<T>::print_subtree(AVLNode *ptr){
  if(ptr != nullptr){
    std::cout << "Value is " << ptr->value << std::endl;
    std::cout << "LeftChild: " << std::endl;
    print_subtree(ptr->left);
    std::cout << "RightChild: " << std::endl;
    print_subtree(ptr->right);
  }
}


#endif

