#pragma once
#include <string>
#include <vector>
extern "C++" {
std::vector<int> prefix_function(std::string str);
std::vector<int> z_function(std::string str);
int z_search_substring(std::string haystack, std::string needle);
int substring_search_prefix(std::string haystack, std::string needle);
std::vector<int> kmp(std::string haystack, std::string needle);
int bm(std::string haystack, std::string needle);
}
