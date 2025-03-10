#include <bits/stdc++.h>
#include <iterator>

using namespace std;

vector<vector<int>> g;
vector<char> used;

// TODO: returns nullptr in 0 -> 1 vertex at the first test
vector<int>* dfs(int v1, int v2) {
	if(v1 == v2) {
		vector<int>* result = new vector<int>();
		result->push_back(v1 + 1);
		return result;
	}
	used[v1] = true;
	for(int u : g[v1]) {
		if(!used[u]) {
			used[u] = true;
			auto* result = dfs(u, v2);
			if(result != nullptr && !result->empty()) {
				result->push_back(v1 + 1);
				return result;
			}
		}
	}
	return nullptr;
}

int main() {
	cin.tie();
	ios_base::sync_with_stdio(false);
	int n, v1, v2;
	cin >> n >> v1 >> v2;
	--v1, --v2;
	for(int i = 0; i < n; ++i) {
		g.push_back(vector<int>(n, 0));
		for(int j = 0; j < n; ++j) {
			cin >> g[i][j];
		}
	}
	used.assign(n, false);
	auto* path = dfs(v1, v2);
	if(path == nullptr) {
		cout << "-1\n";
	} else {
		cout << path->size() << '\n';
		std::copy(path->rbegin(), path->rend(), ostream_iterator<int>(cout, " "));
	}
	return 0;
}
