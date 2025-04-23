#include "sortings.h"

namespace Sortings {
	void merge(std::vector<int>::iterator array, size_t left, size_t mid_index, size_t right) {
		auto mid = array + mid_index;
		auto end = array + right;
		size_t full_size = right - left;
		auto it1 = array + left;
		auto it2 = mid;
		std::vector<int> result(full_size);
		size_t result_index = 0;
		while(it1 < mid && it2 < end) {
			if(*it1 < *it2) {
				result[result_index++] = *it1;
				++it1;
			} else {
				result[result_index++] = *it2;
				++it2;
			}
		}
		while(it1 < mid) {
			result[result_index++] = *it1;
			++it1;
		}
		while(it2 < end) {
			result[result_index++] = *it2;
			++it2;
		}
		std::copy(result.begin(), result.end(), array + left);
	}
	void merge_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
		size_t size = end - begin;
		for(size_t i = 1; i < size; i *= 2) {
			for(size_t j = 0; j < size - i; j += 2 * i) {
				merge(begin, j, j + i, std::min(j + 2 * i, size));
			}
		}
	}
}
