#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <toml++/toml.hpp>
#include <LuaCpp/LuaCpp.hpp>

#include "scenarios.h"
#include "sortings.h"

void execute_task(std::unique_ptr<Scenarios::TaskBase> task) {
	auto ref = task.get();
	ref->print_input();
	ref->run();
	ref->print_output();
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <toml scenario> [task]\n";
		return 1;
	}

	std::string file_path(argv[1]);
	Scenarios::Scenario scenario;
	try {
		scenario = Scenarios::Scenario(file_path);
	} catch(const toml::parse_error& error) {
		std::cerr << "Parse error:\n" << error << std::endl;
		return 1;
	}

	if(argc >= 3) {
		for(int i = 2; i < argc; ++i) {
			execute_task(std::move(scenario.tasks[std::string(argv[i])]));
		}
	} else {
		for(auto t = scenario.tasks.begin(); t != scenario.tasks.end(); ++t) {
			execute_task(std::move(t->second));
		}
	}

	/*std::vector<int> v;
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
    std::cout << '\n';*/

    return 0;
}
