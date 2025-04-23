#include <algorithm>
#include <iostream>
#include <vector>
namespace Sortings {
	void counting_sort(std::vector<int, std::allocator<int>>& arr);
	void radix_sort_lsd(std::vector<int>& arr);
	void quick_sort(std::vector<int>& arr, bool debug = false);
	void merge_sort(std::vector<int>& arr, bool debug = false);
	void heap_sort(std::vector<int>& arr, bool debug = false);
}
