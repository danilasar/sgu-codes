#include "utils.h"
#include <iostream>
#include <iterator>

namespace Utils {
	void print_array(std::vector<int>& data) {	
    std::copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << std::endl;
	}
}
