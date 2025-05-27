#include "utils.h"
#include "avl_tree.h"
#include "scenarios.h"
#include <stdexcept>

namespace Scenarios {

	Task<Algorithms::AVL_TREE>::Task(std::string name, const toml::table& table) : TaskBase(name, table)  {
		auto& tree = this->tree;
		lua.runtime.set("tree", &tree);
		if(!!table["data"]) {
			if(const toml::array* arr = table["data"].as_array()) {
				bool dbug = this->debug;
				for(const auto& elem : *arr) {
					elem.visit([&tree, &dbug](auto&& el) noexcept {
						if constexpr (toml::is_number<decltype(el)>) {
							tree.insert(*el);
							if(dbug) {
								std::cout << "Добавляю элемент " << *el << ':' << std::endl;
								tree.print();
							}
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
	void Task<Algorithms::AVL_TREE>::print_input() {

	}
	void Task<Algorithms::AVL_TREE>::run() {
		lua.runtime.script(script);
	}
	void Task<Algorithms::AVL_TREE>::print_output() {

	}
}
