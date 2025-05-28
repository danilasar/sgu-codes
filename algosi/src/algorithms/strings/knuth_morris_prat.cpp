#include <iostream>
#include <vector>
#include "strings.h"
        
std::vector<int> kmp(std::string haystack, std::string needle) {
    int needle_length = needle.length();
    int haystack_length = haystack.length();
    std::vector<int> answer(haystack_length);
    
    // Значение префикс-функции
    std::vector<int> p = prefix_function(needle + "#" + haystack);
    
    int count = 0;
    for (size_t i = needle_length; i < p.size(); i++) {
        if (p[i] == needle_length) {
            answer[count++] = static_cast<int>(i) - 2 * needle_length + 1; // + если считать с 1
        }
    }
    return answer;
}
