#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<char> used; // bool слишком умный

void dfs(int v) {
	used[v] = true;
	for(int u : g[v]){
		if(!used[u])
			dfs(u);
	}
}

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int v, u;
		cin >> v >> u;
		--v, --u;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	used.assign(n, false);
	int s;
	cin >> s;
	--s;
	dfs(s);
}
