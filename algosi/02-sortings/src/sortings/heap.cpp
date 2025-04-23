#include "sortings.h"
#include "utils.h"

namespace Sortings {
	void heapify_down(std::vector<int>& arr, size_t n, size_t i) {
	    size_t largest = i;
	    size_t left = 2 * i + 1;
	    size_t right = 2 * i + 2;
	
	    if (left < n && arr[left] > arr[largest]) {
	        largest = left;
	    }
	    if (right < n && arr[right] > arr[largest]) {
	        largest = right;
	    }
	    if (largest != i) {
	        std::swap(arr[i], arr[largest]);
	        heapify_down(arr, n, largest);
	    }
	}
	
	void make_heap(std::vector<int>& arr) {
	    size_t n = arr.size();
	    for (int i = (n / 2) - 1; i >= 0; --i) {
	        heapify_down(arr, n, i);
	    }
	}
	
	// Удаляет самый большой (т. е. корневой) элемент кучи
	void pop_heap(std::vector<int>& arr, size_t n) {
	    if (n <= 1) return;
	    std::swap(arr[0], arr[n - 1]);
	    heapify_down(arr, n - 1, 0);
	}

	void heap_sort(std::vector<int>& arr, bool debug) {
		if (arr.size() <= 1) return;
    make_heap(arr.begin(), arr.end());
		if(debug) {
			std::cout << ' ';
			Utils::print_array(arr);
		}
    for (size_t i = arr.size() - 1; i > 0; --i) {
      pop_heap(arr.begin(), arr.begin() + i + 1);
			if(debug) {
				std::cout << " i = " << i << ":\n  ";
				Utils::print_array(arr);
			}
    }
	}
}
