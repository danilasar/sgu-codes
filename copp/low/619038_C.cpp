#include <bits/stdc++.h>
#define MANY_TESTS

using namespace std;

void solve(int&& a, int&& b) {
  int i = 1e9;
  for(int j = (b == 1 ? 1 : 0); j < 40; ++j) {
    int cur_a = a, cur_b = b + j;
    int cur_i = j;
    while(cur_a > 0) {
      cur_a /= cur_b;
      ++cur_i;
    }
    i = min(i, cur_i);
  }
  cout << i << endl;
}

int main() {
#ifdef MANY_TESTS
  int t;
  cin >> t;
  for(int i = 0; i < t; ++i) {
#endif
    int a, b;
    cin >> a >> b;
    solve(move(a), move(b));
#ifdef MANY_TESTS
  }
#endif
  return 0;
}
