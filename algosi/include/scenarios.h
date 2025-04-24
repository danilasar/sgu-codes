#pragma once
#include "algorithms.h"
#include "binary_tree.h"
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <toml++/toml.hpp>
#include <sol/sol.hpp>

namespace Scenarios {
	struct TaskBase {
		std::string name;
		Algorithms::Algorithm algorithm;
		bool debug;
		TaskBase(std::string name, const toml::table& table);
		virtual ~TaskBase() {}
		virtual void run() = 0;
		virtual void print_input() = 0;
		virtual void print_output() = 0;
	};

	struct SortingTask : TaskBase {
		std::vector<int> data;
		void set_data(const std::vector<int>& data);
		void generate_data(size_t size, int min_value, int max_value);
		SortingTask(std::string name, const toml::table& table);
		void print_input() override;
		void print_output() override;
	};

	template<Algorithms::Algorithm T>
	struct Task : TaskBase {};

	template<>
	struct Task<Algorithms::BINARY_TREE> : TaskBase {
		BinaryTree<int> tree;
		sol::state lua;
		std::string script;
		Task(std::string name, const toml::table& table);
		void print_input() final;
		void run() final;
		void print_output() final;
	};

	template<>
	struct Task<Algorithms::COUNTING_SORT> : SortingTask {
		using SortingTask::SortingTask;
		void run() final;
	};
	template<>
	struct Task<Algorithms::HEAP_SORT> : SortingTask {
		using SortingTask::SortingTask;
		void run() final;
	};
	template<>
	struct Task<Algorithms::MERGE_SORT> : SortingTask {
		using SortingTask::SortingTask;
		void run() final;
	};
	template<>
	struct Task<Algorithms::QUICK_SORT> : SortingTask {
		using SortingTask::SortingTask;
		void run() final;
	};
	template<>
	struct Task<Algorithms::RADIX_SORT> : SortingTask {
		using SortingTask::SortingTask;
		void run() final;
	};

	struct Scenario {
		std::map<std::string, std::unique_ptr<TaskBase>> tasks;
		std::vector<std::unique_ptr<TaskBase>> get_tasks();
		Scenario() = default;
		explicit Scenario(std::string path_to_toml);
		static TaskBase* parse_task(std::string name, const toml::table& table);
	};
}
