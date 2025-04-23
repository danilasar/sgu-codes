#include "sortings.h"
#include "utils.h"

namespace Sortings {
	void merge(std::vector<int>& array, size_t left, size_t mid_index, size_t right, bool debug = false) {
		auto it1 = array.begin() + left;
		auto it2 = array.begin() + mid_index;
		auto end1 = array.begin() + mid_index;
		auto end2 = array.begin() + right;
		std::vector<int> result;
		result.reserve(right - left);
		if(debug) {
			std::cout << " array:\n  ";
			Utils::print_array(array);
			std::cout << " result:\n  ";
			Utils::print_array(array);
		}
	
		while (it1 < end1 && it2 < end2) {
			if(debug) {
				std::cout
					<< " it1 = " << it1 - array.begin()
					<< ", end1 = " << end1 - array.begin()
					<< ", it2 = " << it2 - array.begin()
					<< ", end2 = " << end2 - array.begin() << '\n';
			}
			if (*it1 < *it2) {
				result.push_back(*it1);
				++it1;
			} else {
				result.push_back(*it2);
				++it2;
			}
			if(debug) {
				std::cout << "  array:\n   ";
				Utils::print_array(array);
				std::cout << "  result:\n   ";
				Utils::print_array(array);
			}
		}
		while (it1 < end1) {
			if(debug) {
				std::cout
					<< " it1 = " << it1 - array.begin()
					<< ", end1 = " << end1 - array.begin() << '\n';
			}
			result.push_back(*it1);
			++it1;
			if(debug) {
				std::cout << "  array:\n   ";
				Utils::print_array(array);
				std::cout << "  result:\n   ";
				Utils::print_array(array);
			}
		}
		while (it2 < end2) {
			if(debug) {
				std::cout
					<< "it2 = " << it2 - array.begin()
					<< ", end2 = " << end2 - array.begin() << '\n';
			}
			result.push_back(*it2);
			++it2;
			if(debug) {
				std::cout << "  array:\n   ";
				Utils::print_array(array);
				std::cout << "  result:\n   ";
				Utils::print_array(array);
			}
		}
		std::copy(result.begin(), result.end(), array.begin() + left);
	}
	
	void merge_sort(std::vector<int>& arr, bool debug) {
		std::vector<int>::iterator begin = arr.begin();
		std::vector<int>::iterator end = arr.end();
		size_t size = end - begin;
		for (size_t width = 1; width < size; width *= 2) {
			for (size_t i = 0; i < size; i += 2 * width) {
				size_t left = i;
				size_t mid = std::min(i + width, size);
				size_t right = std::min(i + 2 * width, size);
				if(debug) {
					std::cout << "width = " << width << ", left = i = " << i << ", mid = " << mid << ", right = " << right << ":" << std::endl;
				}
				merge(arr, left, mid, right, debug);
			}
		}
	}
}
