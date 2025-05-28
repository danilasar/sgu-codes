#include "scenarios.h"
#include <stdexcept>

namespace Scenarios {

	void StringTask::set_data(const std::string &haystack, const std::string &needle) {
	  this->haystack = haystack;
	  this->needle = needle;
	}

	StringTask::StringTask(std::string name, const toml::table& table) : TaskBase(name, table) {
	  const toml::node *haystack_node = table.get("haystack");
	  const toml::node *needle_node = table.get("needle");
	  if(haystack_node == nullptr || !haystack_node->is_string()) {
	    throw std::invalid_argument("Не передана строка для дальнейших манипуляций с нею");
	  }
	  set_data(
	    haystack_node->value_or<std::string>(""),
	    needle_node == nullptr
	      ? std::string("")
	      : needle_node->value_or<std::string>("")
	  );

	}

	void StringTask::print_input() {
	  
	}

	void StringTask::print_output() {
	  
	}

}
