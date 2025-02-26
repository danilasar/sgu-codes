#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

void counting_sort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int min_val = *std::min_element(arr.begin(), arr.end());
    int max_val = *std::max_element(arr.begin(), arr.end());
    int range = max_val - min_val + 1;

    if (range > 1000000) {
        std::cerr << "Error: Range too large for counting sort.\n";
        return;
    }

    std::vector<int> count(range, 0);
    std::vector<int> output(arr.size());

    for (int num : arr) count[num - min_val]++;
    for (int i = 1; i < range; ++i) count[i] += count[i - 1];
    for (int i = arr.size() - 1; i >= 0; --i) {
        int pos = count[arr[i] - min_val] - 1;
        output[pos] = arr[i];
        count[arr[i] - min_val]--;
    }

    arr = output;
}

void counting_sort_by_digit(std::vector<int>& arr, int exp) {
    std::vector<int> output(arr.size());
    std::vector<int> count(10, 0);

    for (int num : arr) count[(num / exp) % 10]++;
    for (int i = 1; i < 10; ++i) count[i] += count[i - 1];
    for (int i = arr.size() - 1; i >= 0; --i) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

void radix_sort_lsd_positive(std::vector<int>& arr) {
    if (arr.empty()) return;

    int max_num = *std::max_element(arr.begin(), arr.end());
    for (int exp = 1; max_num / exp > 0; exp *= 10)
        counting_sort_by_digit(arr, exp);
}

void radix_sort_lsd(std::vector<int>& arr) {
    std::vector<int> neg, pos;
    for (int num : arr) {
        if (num < 0) neg.push_back(-num);
        else pos.push_back(num);
    }

    radix_sort_lsd_positive(neg);
    std::reverse(neg.begin(), neg.end());
    for (int& num : neg) num = -num;

    radix_sort_lsd_positive(pos);

    arr.clear();
    arr.insert(arr.end(), neg.begin(), neg.end());
    arr.insert(arr.end(), pos.begin(), pos.end());
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [counting|radix]\n";
        return 1;
    }

    std::string mode(argv[1]);
    std::vector<int> v;
    int num;

    while (std::cin >> num) v.push_back(num);

    if (mode == "counting") counting_sort(v);
    else if (mode == "radix") radix_sort_lsd(v);
    else {
        std::cerr << "Invalid mode. Use 'counting' or 'radix'.\n";
        return 1;
    }

    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    return 0;
}
