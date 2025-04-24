#include "scenarios.h"
#include "utils.h"
#include <iostream>
#include <random>
#include <stdexcept>
#include <toml++/toml.hpp>

namespace Scenarios {
	void SortingTask::set_data(const std::vector<int>& data) {
		this->data = data;
	}
	void SortingTask::generate_data(size_t size, int min_value, int max_value) {
		data.clear();
		std::random_device rdev;
		std::default_random_engine rengine(rdev());
		std::uniform_int_distribution<> unidist(min_value, max_value);
		for(size_t i = 0; i < size; ++i) {
			data.push_back(unidist(rengine));
		}
	}
	SortingTask::SortingTask(std::string name, const toml::table& table) : TaskBase(name, table) {
		if(!!table["data"]) {
			if(const toml::array* arr = table["data"].as_array()) {
				for(const auto& elem : *arr) {
					auto& data = this->data;
					elem.visit([&data](auto&& el) noexcept {
						if constexpr (toml::is_number<decltype(el)>) {
							data.push_back(*el);
						} else {
							std::cerr << "Предупреждение: нечисловые входные данные были опущены" << std::endl;
						}
					});
				}
			} else {
				throw std::invalid_argument("Некорректный формат массива данных задачи");
			}
		} else if(!!table["size"] && !!table["min_value"] && !!table["max_value"]) {
			if constexpr (
				toml::is_number<decltype(table["size"])>
				&& toml::is_number<decltype(table["min_value"])>
				&& toml::is_number<decltype(table["max_value"])>
			) {
				generate_data(*table.get_as<size_t>("size"),
					*table.get_as<int>("min_value"),
					*table.get_as<int>("max_value")
				);
			} else {
				throw std::invalid_argument("Некорректные ограничения рандомайзера");
			}
		} else {
			throw std::invalid_argument("Не могу распарсить ввод");
		}
	}
	void SortingTask::print_input() {
		Utils::print_array(data);
	}
	void SortingTask::print_output() {
		Utils::print_array(data);
	}
}
