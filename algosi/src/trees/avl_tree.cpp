#include "avl_tree.h"

int AVLTree::height(AVLNode *node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::balance_factor(AVLNode *node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

AVLNode *AVLTree::right_rotate(AVLNode *node) {
    AVLNode *leftNode = node->left;
    AVLNode *T2 = leftNode->right;

    leftNode->right = node;
    node->left = T2;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    leftNode->height =
        std::max(height(leftNode->left), height(leftNode->right)) + 1;

    return leftNode;
}

AVLNode *AVLTree::left_rotate(AVLNode *node) {
    AVLNode *rightChild = node->right;
    AVLNode *T2 = rightChild->left;

    rightChild->left = node;
    node->right = T2;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    rightChild->height =
        std::max(height(rightChild->left), height(rightChild->right)) + 1;

    return rightChild;
}

AVLNode *AVLTree::insert_helper(AVLNode *node, int key) {
    if (node == nullptr) {
        return new AVLNode(key); // O(1)
    }
    if (key < node->value) {
        node->left = insert_helper(node->left, key);
    }
    else if (key > node->value) {
        node->right = insert_helper(node->right, key);
    }
    else {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balance_factor(node);

    // Левый левый случай
    if (balance > 1 && key < node->left->value) {
        return right_rotate(node);
    }

    // Левый правый случай
    if (balance < -1 && key > node->right->value) {
        return left_rotate(node);
    }

    // Правый правый случай
    if (balance > 1 && key > node->left->value) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Правый левый случай
    if (balance < -1 && key < node->right->value) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

void AVLTree::print_helper(AVLNode *root, std::string indent, bool last) {
    if (root != nullptr) {

        std::cout << indent;
        if (last) {
            std::cout << "R";
            indent += "   ";
        }
        else {
            std::cout << "L";
            indent += "|  ";
        }
        std::cout << root->value << "(" << root->height << ")" << std::endl;
        print_helper(root->left, indent, false);
        print_helper(root->right, indent, true);
    }
}
void AVLTree::print() {
    if (root == nullptr) {
        std::cout << "У дерева нет корня" << std::endl;
    }
    else {
        print_helper(root, "", true);
    }
}

AVLNode* AVLTree::find(int value) {
	return find_recursive(root, value);
}

AVLNode* AVLTree::find_recursive(AVLNode* node, int value) {
	if (!node || node->value == value) return node;
	if (value < node->value) return find_recursive(node->left, value);
	return find_recursive(node->right, value);
}

AVLNode *AVLTree::min_value_node(AVLNode *node) {
    AVLNode *current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

AVLNode *AVLTree::delete_node(AVLNode *node, int key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->value) {
        node->left = delete_node(node->left, key);
    }
    else if (key > node->value) {
        node->right = delete_node(node->right, key);
    }
    else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode *temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }
            delete temp;
        }
        else {
            AVLNode *temp = min_value_node(node->right);
            node->value = temp->value;
            node->right = delete_node(node->right, temp->value);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balance_factor(node);

    // Левый левый случай
    if (balance > 1 && balance_factor(node->left) >= 0) {
        return right_rotate(node);
    }

    // Левый правый случай
    if (balance > 1 && balance_factor(node->left) < 0) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Правый правый случай
    if (balance < -1 && balance_factor(node->right) <= 0)
        return left_rotate(node);

    // Правый левый случай
    if (balance < -1 && balance_factor(node->right) > 0) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}

void AVLTree::insert(int key) {
    root = insert_helper(root, key);
}

void AVLTree::remove(int key) {
    root = delete_node(root, key);
}
