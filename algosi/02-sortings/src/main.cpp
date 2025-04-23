#include <cmath>
//#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <string>

#include "sortings.h"

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
	else if (mode == "radix") Sortings::radix_sort_lsd(v);
	else if(mode == "quck") Sortings::quick_sort(v);
	else if(mode == "merge") Sortings::merge_sort(v.begin(), v.end());
	else if(mode == "heap") Sortings::heap_sort(v);
	else {
		std::cerr << "Invalid mode. Use 'counting' or 'radix'.\n";
		return 1;
	}

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    return 0;
}
