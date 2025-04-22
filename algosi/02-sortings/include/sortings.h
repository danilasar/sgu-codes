#include <algorithm>
#include <iostream>
#include <vector>
namespace Sortings {
	void counting_sort(std::vector<int, std::allocator<int>>& arr);
	void radix_sort_lsd(std::vector<int>& arr);
	void quick_sort(std::vector<int>& arr);
	void merge(std::vector<int>::iterator array, size_t left, size_t mid_index, size_t right);
	void heap_sort(std::vector<int>& arr);
}
