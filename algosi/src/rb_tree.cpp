#include "rb_tree.h"
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

// Create a new node
RedBlackTree::Node* RedBlackTree::createNode(int value) {
    return new Node(value);
}

// Left rotation
void RedBlackTree::leftTurn(Node*& root, Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;

    if (node->parent) {
        if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
    }

    rightChild->left = node;
    node->parent = rightChild;

    if (!rightChild->parent) {
        root = rightChild;
        root->color = BLACK;
    }
}

// Right rotation
void RedBlackTree::rightTurn(Node*& root, Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;

    if (node->parent) {
        if (node == node->parent->left) {
            node->parent->left = leftChild;
        } else {
            node->parent->right = leftChild;
        }
    }

    leftChild->right = node;
    node->parent = leftChild;

    if (!leftChild->parent) {
        root = leftChild;
        root->color = BLACK;
    }
}

// Find grandparent
RedBlackTree::Node* RedBlackTree::findGrandParent(Node* node) {
    return (node && node->parent) ? node->parent->parent : nullptr;
}

// Find uncle
RedBlackTree::Node* RedBlackTree::findUncle(Node* node) {
    Node* grandParent = findGrandParent(node);
    if (!grandParent)
        return nullptr;
    return (grandParent->left == node->parent) ? grandParent->right
                                               : grandParent->left;
}

// Find sibling
RedBlackTree::Node* RedBlackTree::findSibling(Node* node) {
    if (!node || !node->parent)
        return nullptr;
    return (node->parent->left == node) ? node->parent->right
                                        : node->parent->left;
}

// Insertion cases
void RedBlackTree::insertCase1(Node*& root, Node* node) {
    if (!node->parent) {
        node->color = BLACK;
    } else {
        insertCase2(root, node);
    }
}

void RedBlackTree::insertCase2(Node*& root, Node* node) {
    if (node->parent->color == BLACK)
        return;
    insertCase3(root, node);
}

void RedBlackTree::insertCase3(Node*& root, Node* node) {
    Node* uncle = findUncle(node);
    Node* grandParent = findGrandParent(node);

    if (uncle && uncle->color == RED && node->parent->color == RED) {
        uncle->color = BLACK;
        node->parent->color = BLACK;
        grandParent->color = RED;
        insertCase1(root, grandParent);
    } else {
        insertCase4(root, node);
    }
}

void RedBlackTree::insertCase4(Node*& root, Node* node) {
    Node* grandParent = findGrandParent(node);

    if (node == node->parent->right && grandParent->left == node->parent) {
        leftTurn(root, node->parent);
        node = node->left;
    } else if (node == node->parent->left && grandParent->right == node->parent) {
        rightTurn(root, node->parent);
        node = node->right;
    }
    insertCase5(root, node);
}

void RedBlackTree::insertCase5(Node*& root, Node* node) {
    Node* grandParent = findGrandParent(node);
    grandParent->color = RED;
    node->parent->color = BLACK;

    if (node == node->parent->left && grandParent->left == node->parent) {
        rightTurn(root, grandParent);
    } else {
        leftTurn(root, grandParent);
    }
}

// Public methods
void RedBlackTree::insert(int value) {
    if (!root) {
        root = createNode(value);
        root->color = BLACK;
        return;
    }

    Node* current = root;
    while (true) {
        if (value < current->value) {
            if (!current->left) {
                current->left = createNode(value);
                current->left->parent = current;
                insertCase1(root, current->left);
                return;
            }
            current = current->left;
        } else if (value > current->value) {
            if (!current->right) {
                current->right = createNode(value);
                current->right->parent = current;
                insertCase1(root, current->right);
                return;
            }
            current = current->right;
        } else {
            return; // Value already exists
        }
    }
}

void RedBlackTree::remove(int value) {
    if (!root) return;

    Node* current = root;
    while (current && current->value != value) {
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current) {
        removeOne(root, current);
        delete current;
    }
}

RedBlackTree::Node* RedBlackTree::find(int value) {
    Node* current = root;
    while (current) {
        if (value < current->value) {
            current = current->left;
        } else if (value > current->value) {
            current = current->right;
        } else {
            return current;
        }
    }
    return nullptr;
}

void RedBlackTree::print() {
    if (!root) {
        std::cout << "Empty tree" << std::endl;
        return;
    }

    size_t maxDepth = 0;
    max_height(root, maxDepth);
    const short width = 1 << (maxDepth - 1);
    
    Node ***nodes = new Node **[maxDepth];
    for (size_t i = 0; i < maxDepth; i++) {
        nodes[i] = new Node*[width];
        fill_n(nodes[i], width, nullptr);
    }
    
    printHelper(nodes, root, 0, 0);
    for (size_t i = 0; i < maxDepth; i++) {
        short spacing = (1 << (maxDepth - i - 1)) * 4;
        for (size_t j = 0; j < (1 << i); j++) {
            cout << setw(j == 0 ? spacing / 2 : spacing) << formatNode(nodes[i][j]);
        }
        std::cout << std::endl;
    }

    for (size_t i = 0; i < maxDepth; i++) {
        delete[] nodes[i];
    }
    delete[] nodes;
}

// Helper methods for deletion
void RedBlackTree::deleteCase1(Node*& root, Node* node) {
    if (!node->parent) {
        root = (node->left) ? node->left : node->right;
        if (root)
            root->color = BLACK;
    } else {
        deleteCase2(root, node);
    }
}

void RedBlackTree::deleteCase2(Node*& root, Node* node) {
    Node* sibling = findSibling(node);

    if (sibling && sibling->color == RED) {
        node->parent->color = RED;
        sibling->color = BLACK;

        if (node == node->parent->left) {
            leftTurn(root, node->parent);
        } else {
            rightTurn(root, node->parent);
        }
    }
    deleteCase3(root, node);
}

void RedBlackTree::deleteCase3(Node*& root, Node* node) {
    Node* sibling = findSibling(node);

    if (sibling && node->parent->color == BLACK && sibling->color == BLACK &&
        (!sibling->left || sibling->left->color == BLACK) &&
        (!sibling->right || sibling->right->color == BLACK)) {
        sibling->color = RED;
        deleteCase1(root, node->parent);
    } else {
        deleteCase4(root, node);
    }
}

void RedBlackTree::deleteCase4(Node*& root, Node* node) {
    Node* sibling = findSibling(node);

    if (sibling && node->parent->color == RED && sibling->color == BLACK &&
        (!sibling->left || sibling->left->color == BLACK) &&
        (!sibling->right || sibling->right->color == BLACK)) {
        sibling->color = RED;
        node->parent->color = BLACK;
    } else {
        deleteCase5(root, node);
    }
}

void RedBlackTree::deleteCase5(Node*& root, Node* node) {
    Node* sibling = findSibling(node);

    if (sibling && sibling->color == BLACK) {
        if (node == node->parent->left && sibling->left &&
            sibling->left->color == RED &&
            (!sibling->right || sibling->right->color == BLACK)) {
            sibling->color = RED;
            sibling->left->color = BLACK;
            rightTurn(root, sibling);
        } else if (node == node->parent->right && sibling->right &&
                   sibling->right->color == RED &&
                   (!sibling->left || sibling->left->color == BLACK)) {
            sibling->color = RED;
            sibling->right->color = BLACK;
            leftTurn(root, sibling);
        }
    }
    deleteCase6(root, node);
}

void RedBlackTree::deleteCase6(Node*& root, Node* node) {
    Node* sibling = findSibling(node);

    sibling->color = node->parent->color;
    node->parent->color = BLACK;

    if (node == node->parent->left) {
        if (sibling->right) {
            sibling->right->color = BLACK;
        }
        leftTurn(root, node->parent);
    } else {
        if (sibling->left) {
            sibling->left->color = BLACK;
        }
        rightTurn(root, node->parent);
    }
}

void RedBlackTree::replaceNode(Node*& root, Node* node) {
    Node* replacement = node->left ? node->left : node->right;

    if (replacement) {
        replacement->parent = node->parent;

        if (!node->parent) {
            root = replacement;
        } else if (node == node->parent->left) {
            node->parent->left = replacement;
        } else {
            node->parent->right = replacement;
        }

        if (node->color == BLACK) {
            deleteCase1(root, replacement);
        }
    } else if (!node->parent) {
        root = nullptr;
    } else {
        if (node->color == BLACK) {
            deleteCase1(root, node);
        }

        if (node == node->parent->left) {
            node->parent->left = nullptr;
        } else {
            node->parent->right = nullptr;
        }
    }
}

void RedBlackTree::removeOne(Node*& root, Node* node) {
    if (node->left && node->right) {
        Node* replacement = node->right;
        while (replacement->left) {
            replacement = replacement->left;
        }
        node->value = replacement->value;
        replaceNode(root, replacement);
    } else {
        replaceNode(root, node);
    }
}

// Helper methods for printing
std::string RedBlackTree::formatNode(Node* node) {
    if (!node)
    return "    ";
  string val = to_string(node->value);
  return (node->color == RED ? "R" : "B") + val + string(3 - val.size(), ' ');
}

void RedBlackTree::printHelper(Node*** nodes, Node* current, size_t depth, size_t index) {
  nodes[depth][index] = current;
  if (current->left) {
    printHelper(nodes, current->left, depth + 1, 2 * index);
  }
  if (current->right) {
    printHelper(nodes, current->right, depth + 1, 2 * index + 1);
  }
}

// Helper method for calculating tree height
void RedBlackTree::max_height(Node* root, size_t& max, size_t depth) {
    if (!root) {
        return;
    }

    if (depth > max) {
        max = depth;
    }

    max_height(root->left, max, depth + 1);
    max_height(root->right, max, depth + 1);
}
