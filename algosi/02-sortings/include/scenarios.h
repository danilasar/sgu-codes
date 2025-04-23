#include "algorithms.h"
#include <string>
#include <vector>

namespace Scenarios {
	struct TaskBase {
		std::string name;
		bool debug;
	};

	struct SortingTask : TaskBase {
		std::vector<int> data;
		void set_data(const std::vector<int>& data);
		void generate_data(size_t size, int min_value, int max_value);
	};

	template<Algorithms::Algorithm T>
	struct Task : TaskBase {};

	template<>
	struct Task<Algorithms::COUNTING_SORT> : SortingTask {};
	template<>
	struct Task<Algorithms::HEAP_SORT> : SortingTask {};
	template<>
	struct Task<Algorithms::MERGE_SORT> : SortingTask {};
	template<>
	struct Task<Algorithms::QUICK_SORT> : SortingTask {};
	template<>
	struct Task<Algorithms::RADIX_SORT> : SortingTask {};
}
