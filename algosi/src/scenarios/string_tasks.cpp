#include "algorithms.h"
#include "scenarios.h"
#include "strings.h"
#include "utils.h"

namespace Scenarios {
	Task<Algorithms::Z_FUNC>::Task(std::string name, const toml::table& table) : StringTask(name, table) {}

	void Task<Algorithms::Z_FUNC>::run() {
	  std::vector<int> pref = prefix_function(haystack);
	  std::vector<int> zf = z_function(haystack);
	  std::cout << "Префикс-функция:" << std::endl;
	  Utils::print_array(pref);
	  std::cout << "Z-функция:" << std::endl;
	  Utils::print_array(zf);

	  std::cout << std::endl;

	  int test = substring_search_prefix(haystack, needle);
	  std::cout << test << std::endl;
	  if(test > 1) {
	    std::cout << haystack.substr(test, needle.length()) << std::endl;
	  }
	  test = z_search_substring(haystack, needle);
	  if(test > 1) {
	    std::cout << haystack.substr(test, needle.length()) << std::endl;
	  }

	  std::cout << std::endl;

	  pref = prefix_function(needle + '#' + haystack);
	  zf = z_function(needle + '#' + haystack);
	  std::cout << "Префикс-функция (needle#haystack):" << std::endl;
	  Utils::print_array(pref);
	  std::cout << "Z-функция (needle#haystack):" << std::endl;
	  Utils::print_array(zf);
	}

	Task<Algorithms::KMP_FUNC>::Task(std::string name, const toml::table& table) : StringTask(name, table) {}

	void Task<Algorithms::KMP_FUNC>::run() {
	  std::vector<int> kmpv = kmp(haystack, needle);
	  Utils::print_array(kmpv);
	}

	Task<Algorithms::BM_FUNC>::Task(std::string name, const toml::table& table) : StringTask(name, table) {}

	void Task<Algorithms::BM_FUNC>::run() {
	  std::vector<int> ans = bm(haystack, needle);
	  if(ans.empty()) {
	    std::cout << "Вхождение не найдено" << std::endl;
	  }
	  for(const int i : ans) {
		  std::cout << "Найдено вхождение в позиции " << i << ':' << std::endl;
		  std::cout << haystack.substr(i, needle.length()) << std::endl;
	  }
	}
}
