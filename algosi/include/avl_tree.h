#pragma once
#include <iostream>
#include <string>
struct AVLNode {
    int value;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(int k) : value(k), left(nullptr), right(nullptr), height(1) {
    }
};

struct AVLTree {
    AVLTree() : root(nullptr) {
    }

    void insert(int key);
    void remove(int key);
    void print();

    AVLNode* find(int value);

  private:
    AVLNode *root;

    AVLNode* find_recursive(AVLNode* node, int key);
    int height(AVLNode *node);
    int balance_factor(AVLNode *node);
    AVLNode *right_rotate(AVLNode *y);
    AVLNode *left_rotate(AVLNode *x);
    AVLNode *insert_helper(AVLNode *node, int key);
    AVLNode *min_value_node(AVLNode *node);
    AVLNode *delete_node(AVLNode *node, int key);
    void print_helper(AVLNode *root, std::string indent, bool last);
};
