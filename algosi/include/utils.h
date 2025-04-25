#pragma once
#include <vector>
#include "binary_tree.h"

namespace Utils {
void print_array(std::vector<int>& data);
template<typename T>
void print_tree(Node<T>* root);
}
template<typename T>
void Utils::print_tree(Node<T>* root) {
	std::cout << "Root";
	std::cout << root->key;
}
