#include "binary_tree.h"
#include "scenarios.h"
#include "utils.h"
#include <stdexcept>

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
			"delete_node", &BinaryTree<int>::delete_node
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
		return;
		std::cout << "Симметричный (in order): ";
		std::vector<int> vec = tree.in_order();
    Utils::print_array(vec);
    std::cout << "Прямой (pre order): ";
		vec = tree.pre_order();
    Utils::print_array(vec);
    std::cout << "Обратный: (post order): ";
		vec = tree.post_order();
    Utils::print_array(vec);

    int key = 40;
    Node<int>* found = tree.find(key);
    std::cout << "Вершина " << key << " " << (found ? "" : "не ") << "найдена" << std::endl;

    tree.delete_node(30);
    std::cout << "In-order after deleting 30: ";
		vec = tree.in_order();
    Utils::print_array(vec);
	}
	void Task<Algorithms::BINARY_TREE>::print_output() {

	}
}
