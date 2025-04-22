#include "sortings.h"
namespace Sortings {
	void quick_sort(std::vector<int>& arr) {
		std::random_device rdev;
		std::default_random_engine rengine(rdev());
		auto sort = [&rengine](std::vector<int> &arr) -> std::vector<int>& {
			if(arr.size() <= 1) {
				return arr;
			}
			std::uniform_int_distribution<> unidist(0, arr.size());
			int mean = unidist(rengine);
			// TODO:
			
			std::vector<int> *left = new std::vector<int>(arr.begin(), arr.end());
			return *(new std::vector<int>());
		};
		sort(arr);
	}
}
