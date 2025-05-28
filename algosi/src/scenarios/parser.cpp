#include "algorithms.h"
#include "scenarios.h"
#include <memory>
#include <toml++/toml.hpp>
#include <iostream>


namespace Scenarios {
	Scenario::Scenario(std::string path_to_toml) {
		tasks = std::map<std::string, std::unique_ptr<TaskBase>>();
		toml::table main_table = toml::parse_file(path_to_toml);
		toml::node_view tasks_table = main_table["tasks"];
		for(auto i = tasks_table.as_table()->begin(); i != tasks_table.as_table()->end(); ++i) {
			std::string task_name = i->first.data();
			toml::table* right = i->second.as_table();
			auto* algorithm = right->get("algorithm");
			if(algorithm == nullptr) {
				std::cerr << "Пропускаю " << task_name << ": не указан алгоритм" << std::endl;
				continue;
			}
			auto task = parse_task(task_name, *right);
			if(task == nullptr) {
				std::cerr << "[Предупреждение] Пропускаю некорректное задание" << std::endl;
				continue;
			}
			std::unique_ptr<TaskBase> task_ref = std::unique_ptr<TaskBase>(task);
			tasks[task_name] = std::move(task_ref);
		}
	}

	TaskBase* Scenario::parse_task(std::string name, const toml::table& table) {
		std::string algorithm = table["algorithm"].value<std::string>().value();
		if(algorithm == "counting_sort") {
			return new Task<Algorithms::COUNTING_SORT>(name, table);
		} else if(algorithm == "heap_sort") {
			return new Task<Algorithms::HEAP_SORT>(name, table);
		} else if(algorithm == "merge_sort") {
			return new Task<Algorithms::MERGE_SORT>(name, table);
		} else if(algorithm == "quick_sort") {
			return new Task<Algorithms::QUICK_SORT>(name, table);
		} else if(algorithm == "radix_sort") {
			return new Task<Algorithms::RADIX_SORT>(name, table);
		} else if(algorithm == "binary_tree") {
			return new Task<Algorithms::BINARY_TREE>(name, table);
		} else if(algorithm == "rb_tree") {
			return new Task<Algorithms::RB_TREE>(name, table);
		} else if(algorithm == "avl_tree") {
			return new Task<Algorithms::AVL_TREE>(name, table);
		} else if(algorithm == "z_func") {
			return new Task<Algorithms::Z_FUNC>(name, table);
		} else if(algorithm == "kmp_func") {
			return new Task<Algorithms::KMP_FUNC>(name, table);
		} else if(algorithm == "bm_func") {
			return new Task<Algorithms::BM_FUNC>(name, table);
		} else {
			std::cerr << "[Ошибка] Неизвестный алгоритм: " << algorithm << std::endl;
			return nullptr;
		}
	}

	TaskBase::TaskBase(std::string name, const toml::table& table) : name(name) {
		const auto* debug_value = table.get_as<bool>("debug");
		if(debug_value == nullptr) {
			debug = false;
		} else {
			debug = debug_value->get();
		}
	}
}
