#include <bits/stdc++.h>

using namespace std;

int main() {
  size_t q;
  int n, r;
  cin >> q;
  for(size_t i = 0; i < q; ++i) {
    cin >> n;
    if(n == 1) {
      r = 3;
    } else if(n == 2) {
      r = 2;
    } else if(n == 3) {
      r = 1;
    } else {
      r = n % 2;
    }
    cout << r << endl;
  }
  return 0;
}
