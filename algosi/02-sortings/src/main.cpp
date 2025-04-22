#include <cmath>
//#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>

#include "sortings.h"


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

void heap_sort(std::vector<int>& arr) {

}*/

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " [counting|radix|quick|merge|heap]\n";
		return 1;
	}

	std::string mode(argv[1]);
	std::vector<int> v;
	int num;

	while (std::cin >> num) v.push_back(num);

	if (mode == "counting") Sortings::counting_sort(v);
	/*else if (mode == "radix") radix_sort_lsd(v);
	else if(mode == "quck") quick_sort(v);
	else if(mode == "merge") merge_sort(v.begin(), v.end());
	else if(mode == "heap") heap_sort(v);*/
	else {
		std::cerr << "Invalid mode. Use 'counting' or 'radix'.\n";
		return 1;
	}

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    return 0;
}
