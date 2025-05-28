#include <iostream>
#include <vector>
#include "strings.h"

std::vector<int> prefix_function(std::string str) {
    // Массив под результат префикс функции
    std::vector<int> prefixArr(str.length());
    prefixArr[0] = 0;

    for (size_t i = 1; i < str.length(); i++) {
        int k = prefixArr[i - 1];

        while (k > 0 && str[i] != str[k]) {
            k = prefixArr[k - 1];
        }

        if (str[i] == str[k]) {
            k++;
        }
        prefixArr[i] = k;
    }
    return prefixArr;
}
