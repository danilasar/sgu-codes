#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "strings.h"

#define ALPHABET_LEN 256


void pre_bm_bc(std::vector<int> &table, std::string pattern) {
    for (int i = 0; i < ALPHABET_LEN; i++) {
        table[i] = pattern.length();
    }
    for (size_t i = 0; i < pattern.length() - 1; i++) {
        table[pattern[i]] = pattern.length() - 1 - static_cast<int>(i);
    }
}

bool is_prefix(std::string word, int pos) {
    int suffixLen = word.length() - pos;

    for (int i = 0; i < suffixLen; i++) {
        if (word[i] != word[pos + i]) {
            return false;
        }
    }
    return true;
}

int suffix_length(std::string word, int pos) {
    int len = 0;
    for (len = 0;
         (word[pos - len] == word[word.length() - 1 - len]) && (len < pos);
         len++)
        ;
    return len;
}

void pre_bm_gc(std::vector<int> &table, std::string pattern) {
    int lastPrefixIndex = 1;
    // Этап 1: Находим границы совпадений
    for (size_t pos = pattern.length(); pos > 0; pos--) {
        if (is_prefix(pattern, pos)) {
            lastPrefixIndex = pos;
        }
        table[pos] = (pattern.length() - 1 - pos - 1) + lastPrefixIndex;
    }

    // Этап 2: Заполняем таблицу хороших суффиксов
    for (size_t pos = 0; pos < pattern.length() - 1; pos++) {
        int suffixLen = suffix_length(pattern, pos);
        if (pattern[pos - suffixLen] !=
            pattern[pattern.length() - 1 - suffixLen]) {
            table[pattern.length() - 1 - suffixLen] =
                pattern.length() - 1 - pos + suffixLen;
        }
    }
}

int bm(std::string haystack, std::string needle) {
    std::vector<int> badChar(ALPHABET_LEN);
    std::vector<int> goodSuf(needle.length());
    size_t haystack_len = haystack.length();
    size_t needle_len = needle.length();

    pre_bm_bc(badChar, needle);
    pre_bm_gc(goodSuf, needle);

    size_t i = std::max(static_cast<size_t>(1), needle_len) - 1; // Позиция в тексте
    while (i < haystack_len) {
        int j = std::max(static_cast<size_t>(1), needle_len) - 1; // Позиция в шаблоне
        // Сравниваем справа налево
        while (j >= 0 && haystack[i] == needle[j]) {
            --i;
            --j;
        }

        if (j < 0) {
            // Найдено совпадение
            return i + 1;
        }
        // Сдвиг по максимальному из двух правил
        i += std::max(badChar[haystack[i]], goodSuf[j]);
    }
    return -1;
}
