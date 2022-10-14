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
  void balance(AVLNode *);
  void print_subtree(const AVLNode *);
  bool check(const AVLNode *);
  
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
      ptr->left = new AVLNode(_v, ptr);
    }
    else{
      ptr->right = new AVLNode(_v, ptr);
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
  if(!find(_v)){std::cerr << "Cannot pop due to no existing." << std::endl; return;}
  AVLNode *ptr = find_pos(_v);
  AVLNode *pptr = precessor(ptr);
  AVLNode *tr;
  if(pptr != nullptr){
    ptr->value = pptr->value;
    tr = pptr->parent;
    if(pptr == tr->left) tr->left = nullptr;
    else tr->right = nullptr;
    delete pptr;
  }
  else{
    pptr = successor(ptr);
    if(pptr != nullptr){
      ptr->value = pptr->value;
      tr = pptr->parent;
      if(pptr == tr->left) tr->left = nullptr;
      else tr->right = nullptr;
      delete pptr;
    }
    else{
      tr = ptr->parent;
      if(tr == nullptr){
        delete ptr;
        root = nullptr;
        return;
      }
      if(ptr == tr->left) tr->left = nullptr;
      else tr->right = nullptr;
      delete ptr;
    }
  }
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
  if(root == nullptr) std::cerr << "Emptry tree." << std::endl;
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
    root->parent = nullptr;
    ptr->right = root->left;
    if(ptr->right != nullptr)
      ptr->right->parent = ptr;
    root->left = ptr;
    root->left->parent = root;
  }
  else{
    if(p->left == ptr){
      p->left = ptr->right;
      p->left->parent = p;
      ptr->right = p->left->left;
      if(ptr->right != nullptr)
        ptr->right->parent = ptr;
      p->left->left = ptr;
      p->left->left->parent = p->left;
    }
    else{
      p->right = ptr->right;
      p->right->parent = p;
      ptr->right = p->right->left;
      if(ptr->right != nullptr)
        ptr->right->parent = ptr;
      p->right->left = ptr;
      p->right->left->parent = p->right;
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
    root->parent = nullptr;
    ptr->left = root->right;
    if(ptr->left != nullptr)
      ptr->left->parent = ptr;
    root->right = ptr;
    root->right->parent = root;
  }
  else{
    if(p->left == ptr){
      p->left = ptr->left;
      p->left->parent = p;
      ptr->left = p->left->right;
      if(ptr->left != nullptr)
        ptr->left->parent = ptr;
      p->left->right = ptr;
      p->left->parent = p->left;
    }
    else{
      p->right = ptr->left;
      p->right->parent = p;
      ptr->left = p->right->right;
      if(ptr->left != nullptr)
        ptr->left->parent = ptr;
      p->right->right = ptr;
      p->right->parent = p->right;
    }
  }
}

template<typename T>
void AVLTree<T>::maintain_node(AVLNode *ptr){
  if(ptr == nullptr)return;
  balance(ptr);
  if(ptr->skew == 2) {
    if(ptr->left->skew == -1){
      left_rotate(ptr->left);
      balance(ptr->left->left);
      balance(ptr->left);
    }
    right_rotate(ptr);
    balance(ptr);
  }
  else if(ptr->skew == -2){
    if(ptr->right->skew == 1){
      right_rotate(ptr->right);
      balance(ptr->right->right);
      balance(ptr->right);
    }
    left_rotate(ptr);
    balance(ptr);
  }
  maintain_node(ptr->parent);
}


template<typename T>
void AVLTree<T>::balance(AVLNode *ptr)
{
  AVLNode *_l = ptr->left;
  AVLNode *_r = ptr->right;
  int lh = -1;
  int rh = -1;
  if(_l != nullptr) lh = _l->height;
  if(_r != nullptr) rh = _r->height;
  ptr->height = std::max(lh, rh) + 1;
  ptr->skew = lh - rh;
}

template<typename T>
void AVLTree<T>::print_subtree(const AVLNode *ptr){
  if(ptr != nullptr){
    std::cout << "Value is " << ptr->value << std::endl;
    std::cout << "LeftChild: " << std::endl;
    print_subtree(ptr->left);
    std::cout << "RightChild: " << std::endl;
    print_subtree(ptr->right);
  }
}

template<typename T>
bool AVLTree<T>::check(const AVLNode *ptr){
  if(ptr == nullptr) return true;
  if(ptr->parent == nullptr && ptr != root){
    std::cout << "root wrong" << std::endl;
    return false;
  }
  if(ptr->left != nullptr && ptr->left->parent != ptr){
    std::cout << "node " << ptr->value << " left child wrong!" << std::endl;
    return false;
  }
  if(ptr->right != nullptr && ptr->right->parent != ptr){
    std::cout << "node " << ptr->value << " right child wrong!" << std::endl;
    return false;
  }
  return check(ptr->left)&&check(ptr->right);
}


  
#endif

