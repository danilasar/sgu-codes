#include "sortings.h"

namespace Sortings {
	void counting_sort_by_digit(std::vector<int>& arr, int exp) {
	    std::vector<int> output(arr.size());
	    std::vector<int> count(10, 0);
	
		    for (int num : arr) count[(num / exp) % 10]++;
	    for (int i = 1; i < 10; ++i) count[i] += count[i - 1];
	    for (int i = arr.size() - 1; i >= 0; --i) {
	        int digit = (arr[i] / exp) % 10;
	        output[count[digit] - 1] = arr[i];
	        count[digit]--;
	    }
	
	    arr = output;
	}
	
	void radix_sort_lsd_positive(std::vector<int>& arr) {
	    if (arr.empty()) return;
	
	    int max_num = *std::max_element(arr.begin(), arr.end());
	    for (int exp = 1; max_num / exp > 0; exp *= 10)
	        counting_sort_by_digit(arr, exp);
	}
	
	void radix_sort_lsd(std::vector<int>& arr) {
	    std::vector<int> neg, pos;
	    for (int num : arr) {
	        if (num < 0) neg.push_back(-num);
	        else pos.push_back(num);
	    }
	
	    radix_sort_lsd_positive(neg);
	    std::reverse(neg.begin(), neg.end());
	    for (int& num : neg) num = -num;
	
	    radix_sort_lsd_positive(pos);
	
	    arr.clear();
	    arr.insert(arr.end(), neg.begin(), neg.end());
	    arr.insert(arr.end(), pos.begin(), pos.end());
	}
}
