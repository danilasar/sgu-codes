#include <iostream>
#include <string>
#include <vector>
#include "strings.h"

std::vector<int> z_function(std::string str) {
    // Массив под результат z-функции
    std::vector<int> zf(str.length());

    int left = 0, right = 0;

    for (size_t i = 1; i < str.length(); i++) {
        zf[i] = std::max(0, std::min(right - static_cast<int>(i), zf[static_cast<int>(i) - left]));

        while (i + zf[i] < str.length() && str[zf[i]] == str[i + zf[i]]) {
            zf[i]++;
        }
        if (i + zf[i] > static_cast<size_t>(right)) {
            left = i;
            right = i + zf[i];
        }
    }
    return zf;
}

int z_search_substring(std::string haystack, std::string needle) {
    // Массив z-функции
    std::vector<int> zf = z_function(needle + '#' + haystack);

    // Проходимся по массиву
    for (size_t i = needle.length(); i < zf.size(); i++) {
        // Если z-функция равна длине needle, то нашли needle
        if (static_cast<size_t>(zf[i]) == needle.length()) {
            // Выводим найденный индекс
            return i - needle.length() - 1;
        }
    }
    return -1;
}
int substring_search_prefix(std::string haystack, std::string needle) {
    // Массив z-функции
    std::vector<int> prefixArr = prefix_function(needle + '#' + haystack);

    // Проходимся по массиву
    for (size_t i = needle.length(); i < prefixArr.size(); i++) {
        // Если префикс функция равна длине needle, то нашли needle
        if (static_cast<size_t>(prefixArr[i]) == needle.length()) {
            // Выводим найденный индекс
            return i - (needle.length() * 2);
        }
    }
    return -1;
}
