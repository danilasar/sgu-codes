#include "algorithms.h"
#include "lua.h"
#include "binary_tree.h"
#include "rb_tree.h"
#include "utils.h"
#include <lua.h>

void _print_tree(BinaryTree<int>* tree) { Utils::print_tree<int>(tree->get_root()); }
void print_node(Node<int>* node) { std::cout << node->key; }
Node<int>* get_left(Node<int>* node) { return node->left; }
Node<int>* get_right(Node<int>* node) { return node->right; }

Lua::Lua() {
	init_lua();
}

void Lua::init_lua() {
	runtime = sol::state();
	
	runtime.open_libraries(sol::lib::base);
	sol::usertype<BinaryTree<int>> binary_tree = runtime.new_usertype<BinaryTree<int>>(
		"BinaryTree",
		"get_root", &BinaryTree<int>::get_root,

		"in_order", &BinaryTree<int>::in_order,
		"pre_order", &BinaryTree<int>::pre_order,
		"post_order", &BinaryTree<int>::post_order,

		"find", &BinaryTree<int>::find,
		"add_node", &BinaryTree<int>::add_node,
		"delete_node", &BinaryTree<int>::delete_node,
		"print_tree", &BinaryTree<int>::print,
		"print", &_print_tree
	);
	runtime["print_array"] = &Utils::print_array;
	runtime["print_node"] = &print_node;
	runtime["get_left"] = &get_left;
	runtime["get_right"] = &get_right;
	sol::usertype<RedBlackTree> rb_tree = runtime.new_usertype<RedBlackTree>(
		"RedBlackTree",
		
		"insert", &RedBlackTree::insert,
		"remove", &RedBlackTree::remove,
		"find", &RedBlackTree::find,
		"print", &RedBlackTree::print
	);
}
