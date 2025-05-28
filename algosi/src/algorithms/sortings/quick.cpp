#include "sortings.h"
#include "utils.h"
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
		partition_sort = [&arr, &rengine, &partition_sort, debug](int low, int high) {
			if(debug) {
				std::cout << "partition_sort(low = " << low << ", high = " << high << "):" << std::endl;
			}
			if(low >= high) {
				if(debug) {
					std::cout << " low >= high." << std::endl << std::endl;
				}
				return;
			}
			std::uniform_int_distribution<> unidist(0, high - low);
			int pivot_index = low + unidist(rengine);
			int pivot = arr[pivot_index];
			if(debug) {
				std::cout << " pivot: arr[" << pivot_index << "] = " << pivot << std::endl;
			}
			std::swap(arr[pivot_index], arr[high]);
			if(debug) {
				std::cout << " Меняю местами arr[" << pivot_index << "] и arr[" << high << "]" << std::endl << ' ';
				Utils::print_array(arr);
			}
			int i = low - 1;
			for(int j = low; j < high; ++j) {
				if(debug) {
					std::cout << " i = " << i << ", j = " << j << ":\n ";
					Utils::print_array(arr);
				}
				if(arr[j] <= pivot) {
					i++;
					std::swap(arr[i], arr[j]);
				}
			}
			if(debug) {
				std::cout << ' ';
				Utils::print_array(arr);
			}
			std::swap(arr[i + 1], arr[high]);
			if(debug) {
				std::cout << " Меняю местами arr[" << i + 1 << "] и arr[" << high << "]" << std::endl << ' ';
				Utils::print_array(arr);
			}
			int pivot_pos = i + 1;
			if(debug) {
				std::cout << "Новая опорная точка: " << pivot_pos << std::endl;
				std::cout << "Порождаю рекурсии:\n";			
				std::cout << " partition_sort(" << low << ", " << pivot_pos - 1 << ");\n";
				std::cout << " partition_sort(" << pivot_pos + 1 << ", " << high << ");\n";
				std::cout << std::endl;
			}
			partition_sort(low, pivot_pos - 1);
			partition_sort(pivot_pos + 1, high);
		};
		partition_sort(0, arr.size() - 1);
	}
}
