#pragma once
#include <cmath>
#include <bits/stdc++.h>
#include <iostream>
#include <queue>
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
	Node<T>* get_root();
	Node<T>* find(T key);
	std::vector<T> in_order();
	std::vector<T> pre_order();
	std::vector<T> post_order();
	void print_tree_vertical(Node<T>* node, int space = 0, int indent = 4);
	void print() const;

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
	int get_height(Node<T>* node) const;
    void print_helper(std::vector<std::vector<Node<T>*>>& arr, Node<T>* x, int deepness, int ind) const;
    std::string format_node(Node<T>* node) const;
};

template <typename T>
void BinaryTree<T>::print() const {
    if (!root) return;

    int max_height = get_height(root);
    int offset = 1;
    int width = 1;
    for (int i = 1; i < max_height; ++i) offset <<= 1;

    // Создаем двумерный массив указателей на узлы
    std::vector<std::vector<Node<T>*>> arr(max_height);
    for (int i = 0, w = 1; i < max_height; ++i, w <<= 1)
        arr[i].resize(w, nullptr);

    print_helper(arr, root, 0, 0);

    int curr_offset = offset;
    int curr_width = 1;
    for (int i = 0; i < max_height; ++i) {
        std::cout << std::setw((curr_offset >> 1) + 1);
        std::cout << format_node(arr[i][0]);
        for (int j = 1; j < curr_width; ++j) {
            std::cout << std::setw(curr_offset);
            std::cout << format_node(arr[i][j]);
        }
        curr_offset >>= 1;
        curr_width <<= 1;
        std::cout << std::endl;
    }
}

// Вспомогательные методы для печати
template <typename T>
int BinaryTree<T>::get_height(Node<T>* node) const {
    if (!node) return 0;
    return 1 + std::max(get_height(node->left), get_height(node->right));
}

template <typename T>
void BinaryTree<T>::print_helper(std::vector<std::vector<Node<T>*>>& arr, Node<T>* x, int deepness, int ind) const {
    arr[deepness][ind] = x;
    if (x && x->left) {
        print_helper(arr, x->left, deepness + 1, 2 * ind);
    }
    if (x && x->right) {
        print_helper(arr, x->right, deepness + 1, 2 * ind + 1);
    }
}

template <typename T>
std::string BinaryTree<T>::format_node(Node<T>* node) const {
    if (!node) return " ";
    return std::to_string(node->key);
}

template <typename T>
void BinaryTree<T>::print_tree_vertical(Node<T>* node, int space, int indent) {
		if(node == nullptr) return;

    // Сначала печатаем правое поддерево
    print_tree_vertical(node->right, space + indent, indent);

    // Печатаем текущий узел с отступом
    std::cout << std::setw(space) << "" << node->key << std::endl;

    // Затем печатаем левое поддерево
    print_tree_vertical(node->left, space + indent, indent);
    /*if (!root) {
        std::cout << "<empty tree>\n";
        return;
    }

    // Узнаём высоту дерева
    std::function<int(Node<T>*)> tree_height = [&](Node<T>* node) {
        if (!node) return 0;
        return 1 + std::max(tree_height(node->left), tree_height(node->right));
    };
    int height = tree_height(root);

    // Используем очередь для обхода по уровням
    std::queue<Node<T>*> q;
    q.push(root);

    int max_width = std::pow(2, height) * 4; // ширина для форматирования

    for (int level = 0; level < height; ++level) {
        int level_nodes = std::pow(2, level);
        int space_between = max_width / level_nodes;
        int first_space = space_between / 2;

        // Выводим узлы текущего уровня
        for (int i = 0; i < level_nodes; ++i) {
            Node<T>* node = q.front();
            q.pop();

            if (i == 0)
                std::cout << std::setw(first_space) << "";

            if (node) {
                std::cout << node->key;
                q.push(node->left);
                q.push(node->right);
            } else {
                std::cout << " ";
                q.push(nullptr);
                q.push(nullptr);
            }
            std::cout << std::setw(space_between) << "";
        }
        std::cout << "\n";
    }*/
}

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
Node<T>* BinaryTree<T>::get_root() {
	return root;
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
