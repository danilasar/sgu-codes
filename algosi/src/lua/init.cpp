#include "lua.h"
#include "binary_tree.h"
#include "utils.h"

void _print_tree(BinaryTree<int>* tree) { Utils::print_tree<int>(tree->get_root()); }

Lua::Lua() {
	init_lua();
}

void Lua::init_lua() {
	runtime = sol::state();
	
	runtime.open_libraries(sol::lib::base);
	sol::usertype<BinaryTree<int>> binary_tree = runtime.new_usertype<BinaryTree<int>>(
		"BinaryTree",

		"in_order", &BinaryTree<int>::in_order,
		"pre_order", &BinaryTree<int>::pre_order,
		"post_order", &BinaryTree<int>::post_order,

		"find", &BinaryTree<int>::find,
		"add_node", &BinaryTree<int>::add_node,
		"delete_node", &BinaryTree<int>::delete_node,
		"print", &_print_tree
	);
	runtime["print_array"] = &Utils::print_array;
}
