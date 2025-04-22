#include <algorithm>
#include <iostream>
#include <vector>
#include "counting.h"

namespace Sortings {
	void counting_sort(std::vector<int, std::allocator<int>>& arr) {
	    if (arr.empty()) return;
	
	    int min_val = *std::min_element(arr.begin(), arr.end());
	    int max_val = *std::max_element(arr.begin(), arr.end());
	    int range = max_val - min_val + 1;
	
		std::cout << "Biba\n";
	
	    if (range > 1000000) {
	        std::cerr << "Error: Range too large for counting sort.\n";
	        return;
	    }
	
	    std::vector<int, std::allocator<int>> count(range, 0);
	    std::vector<int, std::allocator<int>> output(arr.size());
	
	    for (int num : arr) count[num - min_val]++;
	    for (int i = 1; i < range; ++i) count[i] += count[i - 1];
	    for (int i = arr.size() - 1; i >= 0; --i) {
	        int pos = count[arr[i] - min_val] - 1;
	        output[pos] = arr[i];
	        count[arr[i] - min_val]--;
	    }
	
	    arr = output;
	}
}
