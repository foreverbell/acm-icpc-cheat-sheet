int n, m, vis[maxn], level[maxn], pr[maxn], pr2[maxn];
vector<int> edge[maxn]; // for Left

bool dfs(int u) {
	vis[u] = true;
	for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
		int v = pr2[*it];
		if (v == -1 || (!vis[v] && level[u] < level[v] && dfs(v))) {
			pr[u] = *it, pr2[*it] = u;
			return true;
		}
	}
	return false;
}

int hopcroftKarp() {
	memset(pr, -1, sizeof(pr)); memset(pr2, -1, sizeof(pr2));
	for (int match = 0; ;) {
		queue<int> Q;
		for (int i = 1; i <= n; ++i) {
			if (pr[i] == -1) {
				level[i] = 0;
				Q.push(i);
			} else level[i] = -1;
		}
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
				int v = pr2[*it];
				if (v != -1 && level[v] < 0) {
					level[v] = level[u] + 1;
					Q.push(v);
				}
			}
		}
		for (int i = 1; i <= n; ++i) vis[i] = false;
		int d = 0;
		for (int i = 1; i <= n; ++i) if (pr[i] == -1 && dfs(i)) ++d;
		if (d == 0) return match;
		match += d;
	}
}