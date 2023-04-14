#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <memory>
#include <utility>
#include <stack>

template<typename Key, typename Value>
class RBTree
{
private:
    enum class Color {red, black};

    struct node {
        Key key;
        Value value;
        std::unique_ptr<node> left;
        std::unique_ptr<node> right;
        Color color;
        explicit node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr), color(Color::red) {}
    };

    std::unique_ptr<node> root;

    void rotateLeft(std::unique_ptr<node>& x) {
        auto y = std::move(x->right);
        x->right = std::move(y->left);
        y->left = std::move(x);
        y->color = y->left->color;
        x = std::move(y);
        x->color = Color::red;
    }

    void rotateRight(std::unique_ptr<node>& x) {
        std::cout << "here2" << std::endl;
        auto y = std::move(x->left);
        x->left = std::move(y->right);
        y->right = std::move(x);
        y->color = y->right->color;
        x = std::move(y);
        x->color = Color::red;
    }

    void flipColors(std::unique_ptr<node>& x) {
        x->color = Color::red;
        x->left->color = Color::black;
        x->right->color = Color::black;
    }

    bool isRed(const std::unique_ptr<node>& x) const {
        return (x != nullptr) && (x->color == Color::red);
    }

    void insert(std::unique_ptr<node>& x, const Key& key, const Value& value) {
        if(x == nullptr) {
            x = std::make_unique<node>(key, value);
            return;
        }

        if(key < x->key) 
            insert(x->left, key, value);
        else if(key > x->key)
            insert(x->right, key, value);
        else {
            x->value = value;
            return;
        }

        if(isRed(x->right) && !isRed(x->left)) 
            rotateLeft(x);

        if(isRed(x->left) && isRed(x->left->left)) 
            rotateRight(x);

        if(isRed(x->left) && isRed(x->right))
            flipColors(x);

    }

    std::pair<std::unique_ptr<node>, std::unique_ptr<node>> getMinAndRemoveMin(std::unique_ptr<node> x) {
        if(x->left != nullptr) 
            return {std::move(x->right), std::move(x)};
        auto [l, m] = getMinAndRemoveMin(std::move(x->left));
        x->left = std::move(l);

        return {std::move(x), std::move(m)};
    }

    void remove(std::unique_ptr<node>& x, const Key& key) {
        if(x == nullptr)
            return;
        if(key < x->key) 
            remove(x->left, key);
        else if(key > x->key)
            remove(x->right, key);
        else {
            if(x->left == nullptr) {
                x = std::move(x->right);
                return;
            }
            if(x->right == nullptr) {
                x = std::move(x->left);
                return;
            }

            auto [r, min] = getMinAndRemoveMin(std::move(x->right));
            min->left = std::move(x->left);
            min->right = std::move(r);
            x = std::move(min);
        }

        if(isRed(x->right) && !isRed(x->left))
            rotateLeft(x);
        
        if(isRed(x->left) && isRed(x->left->left))
            rotateRight(x);
        
        if(isRed(x->left) && isRed(x->right))
            flipColors(x);
    }

    void inorderTraversal(std::unique_ptr<node>& x) {
        if(x != nullptr) {
            inorderTraversal(x->left);
            std::cout << "(" << x->key << ", "<< x->value << ")" << std::endl;
            inorderTraversal(x->right);
        }
    }

public:
    void insert(const Key& key, const Value& value) {
        insert(root, key, value);
        root->color = Color::black;
    }

    void remove(const Key& key) {
        remove(root, key);
        if(root != nullptr)
            root->color = Color::black;
    }

    bool contains(const Key& key) const {
        auto x = root.get();
        while(x != nullptr) {
            if(key < x->key)
                x = x->left.get();
            else if (key > x->key)
                x = x->right.get();
            else
                return true;
        }
        return false;
    }

    Value operator[](const Key& key) const {
        auto x = root.get();
        while(x != nullptr) {
            if(key < x->key)
                x = x->left.get();
            else if(key > x->key)
                x = x->right.get();\
            else
                return x->value;
        }
        return Value{};
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }

};

#endif // RBTREE_H