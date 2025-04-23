#include "scenarios.h"
#include <random>

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
}
