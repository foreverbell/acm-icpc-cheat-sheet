const int logn = 20;
int parent[maxn], lca[logn][maxn], depth[maxn];

void initLCA() {
	for (int i = 1; i <= n; ++i) lca[0][i] = parent[i];
	for (int j = 1; j < logn; ++j) {
		for (int i = 1; i <= n; ++i) {
			lca[j][i] = lca[j - 1][lca[j - 1][i]];
		}
	}
}

int LCA(int x, int y) {
	if (depth[x] < depth[y]) swap(x, y);
	for (int i = logn - 1; i >= 0; --i) {
		if (depth[x] - (1 << i) >= depth[y]) x = lca[i][x];
	}
	if (x == y) return x;
	for (int i = logn - 1; i >= 0; --i) {
		if (lca[i][x] != lca[i][y]) {
			x = lca[i][x], y = lca[i][y];
		}
	}
	return lca[0][x];
}