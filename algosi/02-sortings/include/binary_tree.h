#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Node {
public:
    T key;
    Node* left;
    Node* right;
    Node(T k);
};

template <typename T>
class BinaryTree {
public:
    BinaryTree();
    ~BinaryTree();

    void add_node(T key);
    void delete_node(T key);
    Node<T>* find(T key);
    std::vector<T> in_order();
    std::vector<T> pre_order();
    std::vector<T> post_order();

private:
    Node<T>* root;

    void destroyTree(Node<T>* node);
    void add_node_recursive(Node<T>* node, T key);
    Node<T>* delete_node_recursive(Node<T>* node, T key);
    Node<T>* find_min(Node<T>* node);
    Node<T>* find_recursive(Node<T>* node, T key);
    void in_order_recursive(Node<T>* node, std::vector<T>& result);
    void pre_order_recursive(Node<T>* node, std::vector<T>& result);
    void post_order_recursive(Node<T>* node, std::vector<T>& result);
};

template <typename T>
Node<T>::Node(T k) : key(k), left(nullptr), right(nullptr) {}

template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

template <typename T>
BinaryTree<T>::~BinaryTree() {
    destroyTree(root);
}

template <typename T>
void BinaryTree<T>::add_node(T key) {
    if (!root) {
        root = new Node<T>(key);
    } else {
        add_node_recursive(root, key);
    }
}

template <typename T>
void BinaryTree<T>::destroyTree(Node<T>* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template <typename T>
void BinaryTree<T>::add_node_recursive(Node<T>* node, T key) {
    if (key < node->key) {
        if (!node->left) {
            node->left = new Node<T>(key);
        } else {
            add_node_recursive(node->left, key);
        }
    } else if (key > node->key) {
        if (!node->right) {
            node->right = new Node<T>(key);
        } else {
            add_node_recursive(node->right, key);
        }
    }
}

template <typename T>
Node<T>* BinaryTree<T>::delete_node_recursive(Node<T>* node, T key) {
    if (!node) return nullptr;

    if (key < node->key) {
        node->left = delete_node_recursive(node->left, key);
    } else if (key > node->key) {
        node->right = delete_node_recursive(node->right, key);
    } else {
        if (!node->left) {
            Node<T>* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            Node<T>* temp = node->left;
            delete node;
            return temp;
        }
        Node<T>* min_node = find_min(node->right);
        node->key = min_node->key;
        node->right = delete_node_recursive(node->right, min_node->key);
    }
    return node;
}

template <typename T>
Node<T>* BinaryTree<T>::find_min(Node<T>* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template <typename T>
void BinaryTree<T>::delete_node(T key) {
    root = delete_node_recursive(root, key);
}

template <typename T>
Node<T>* BinaryTree<T>::find(T key) {
    return find_recursive(root, key);
}

template <typename T>
Node<T>* BinaryTree<T>::find_recursive(Node<T>* node, T key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return find_recursive(node->left, key);
    return find_recursive(node->right, key);
}

template <typename T>
std::vector<T> BinaryTree<T>::in_order() {
    std::vector<T> result;
    in_order_recursive(root, result);
    return result;
}

template <typename T>
void BinaryTree<T>::in_order_recursive(Node<T>* node, std::vector<T>& result) {
    if (node) {
        in_order_recursive(node->left, result);
        result.push_back(node->key);
        in_order_recursive(node->right, result);
    }
}

template <typename T>
std::vector<T> BinaryTree<T>::pre_order() {
    std::vector<T> result;
    pre_order_recursive(root, result);
    return result;
}

template <typename T>
void BinaryTree<T>::pre_order_recursive(Node<T>* node, std::vector<T>& result) {
    if (node) {
        result.push_back(node->key);
        pre_order_recursive(node->left, result);
        pre_order_recursive(node->right, result);
    }
}

template <typename T>
std::vector<T> BinaryTree<T>::post_order() {
    std::vector<T> result;
    post_order_recursive(root, result);
    return result;
}

template <typename T>
void BinaryTree<T>::post_order_recursive(Node<T>* node, std::vector<T>& result) {
    if (node) {
        post_order_recursive(node->left, result);
        post_order_recursive(node->right, result);
        result.push_back(node->key);
    }
}
