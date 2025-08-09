#include <bits/stdc++.h>

using namespace std;

int main() {
  int c, v0, v1, a, l, i = 1;
  bool exceeded = false;
  cin >> c >> v0 >> v1 >> a >> l;
  c = max(0, c - v0);
  v0 = max(0, v0);
  int buf;
  while(c > 0) {
    if(!exceeded) {
      buf = v0 + a * i;
      if(buf > v1) {
        buf = v1;
        exceeded = true;
      }
      buf -= l;
    }
    c -= buf;
    ++i;
  }
  cout << i << endl;
  return 0;
}
