#pragma once
#include <iomanip>
#include <iostream>

enum Color { BLACK, RED };

class RedBlackTree {
public:
    // Node structure
    struct Node {
        Color color;
        int value;
        Node *right;
        Node *left;
        Node *parent;
        
        Node(int val) : value(val), color(RED), right(nullptr), left(nullptr), parent(nullptr) {}
    };
    // Constructors
    RedBlackTree() : root(nullptr) {}
    
    // Public methods
    void insert(int value);
    void remove(int value);
    Node* find(int value);
    void print();
    
private:
    
    // Root pointer
    Node* root;
    
    // Helper methods
    Node* createNode(int value);
    void leftTurn(Node*& root, Node* node);
    void rightTurn(Node*& root, Node* node);
    Node* findGrandParent(Node* node);
    Node* findUncle(Node* node);
    Node* findSibling(Node* node);
    void insertCase1(Node*& root, Node* node);
    void insertCase2(Node*& root, Node* node);
    void insertCase3(Node*& root, Node* node);
    void insertCase4(Node*& root, Node* node);
    void insertCase5(Node*& root, Node* node);
    void deleteCase1(Node*& root, Node* node);
    void deleteCase2(Node*& root, Node* node);
    void deleteCase3(Node*& root, Node* node);
    void deleteCase4(Node*& root, Node* node);
    void deleteCase5(Node*& root, Node* node);
    void deleteCase6(Node*& root, Node* node);
    void replaceNode(Node*& root, Node* node);
    void removeOne(Node*& root, Node* node);
    void printHelper(Node*** nodes, Node* current, size_t depth = 0, size_t index = 0);
    void max_height(Node* root, size_t& max, size_t depth = 1);
    std::string formatNode(Node* node);
};
