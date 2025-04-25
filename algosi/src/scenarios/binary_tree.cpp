#include "utils.h"
#include "binary_tree.h"
#include "scenarios.h"
#include <stdexcept>

void _print_tree(BinaryTree<int>* tree) { Utils::print_tree<int>(tree->get_root()); }

namespace Scenarios {

	Task<Algorithms::BINARY_TREE>::Task(std::string name, const toml::table& table) : TaskBase(name, table)  {
		lua.open_libraries(sol::lib::base);
		sol::usertype<BinaryTree<int>> binary_tree = lua.new_usertype<BinaryTree<int>>(
			"BinaryTree",

			"in_order", &BinaryTree<int>::in_order,
			"pre_order", &BinaryTree<int>::pre_order,
			"post_order", &BinaryTree<int>::post_order,

			"find", &BinaryTree<int>::find,
			"add_node", &BinaryTree<int>::add_node,
			"delete_node", &BinaryTree<int>::delete_node,
			"print", &_print_tree
		);
		lua.set("tree", &tree);
		lua["print_array"] = &Utils::print_array;
		
		auto& tree = this->tree;
		if(!!table["data"]) {
			if(const toml::array* arr = table["data"].as_array()) {
				for(const auto& elem : *arr) {
					elem.visit([&tree](auto&& el) noexcept {
						if constexpr (toml::is_number<decltype(el)>) {
							tree.add_node(*el);
						} else {
							std::cerr << "Предупреждение: нечисловые входные данные были опущены" << std::endl;
						}
					});
				}
			} else {
				throw std::invalid_argument("Некорректный формат массива данных задачи");
			}
		} else {
			throw std::invalid_argument("Не задано содержимое дерева");
		}
		if(!!table["script"]) {	
			const toml::impl::wrap_node<std::string>* script_text = table.get_as<std::string>("script");
			if(script_text == nullptr) {
				std::cerr << "Не могу интерпретировать скрипт как текст" << std::endl;
			}
			script = static_cast<std::string>(*script_text);
		} else {
			std::cerr << "Предупреждение: не задан скрипт тестирования дерева" << std::endl;
		}
	}
	void Task<Algorithms::BINARY_TREE>::print_input() {

	}
	void Task<Algorithms::BINARY_TREE>::run() {
		lua.script(script);
	}
	void Task<Algorithms::BINARY_TREE>::print_output() {

	}
}
