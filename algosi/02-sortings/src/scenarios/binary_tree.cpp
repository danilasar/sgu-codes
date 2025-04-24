#include "binary_tree.h"
#include "scenarios.h"
#include "utils.h"
#include <stdexcept>

namespace Scenarios {

	Task<Algorithms::BINARY_TREE>::Task(std::string name, toml::table& table) : TaskBase(name, table)  {
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
		
	}
	void Task<Algorithms::BINARY_TREE>::print_input() {

	}
	// TODO: конфигурируемость теста
	void Task<Algorithms::BINARY_TREE>::run() {
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
