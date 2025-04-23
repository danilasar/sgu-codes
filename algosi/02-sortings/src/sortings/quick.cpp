#include "sortings.h"
#include <functional>
#include <random>
#include <vector>

namespace Sortings {
	void quick_sort(std::vector<int>& arr, bool debug) {
		std::random_device rdev;
		std::default_random_engine rengine(rdev());
		if(arr.size() <= 1) {
			return;
		}
		std::function<void(int, int)> partition_sort;
		partition_sort = [&arr, &rengine, &partition_sort](int low, int high) {
			if(low >= high) return;
			std::uniform_int_distribution<> unidist(0, high - low);
			int pivot_index = low + unidist(rengine);
			int pivot = arr[pivot_index];
			std::swap(arr[pivot_index], arr[high]);
			int i = low - 1;
			for(int j = low; j < high; ++j) {
				if(arr[j] <= pivot) {
					i++;
					std::swap(arr[i], arr[j]);
				}
			}
			std::swap(arr[i + 1], arr[high]);
			int pivot_pos = i + 1;
			partition_sort(low, pivot_pos - 1);
			partition_sort(pivot_pos + 1, high);
		};
		partition_sort(0, arr.size() - 1);
	}
}
