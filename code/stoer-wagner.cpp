// stoer-wagner algorithm, complexity: O(n^3)
// used to compute the global minimum cut, and self-loop is ignored.
int n, g[maxn][maxn], v[maxn], d[maxn], vis[maxn];
int stoer_wagner(int n) {  
	int res = maxint;
	for (int i = 1; i <= n; i++) v[i] = i, vis[i] = 0;
	while (n > 1) {
		int p = 2, prev = 1;
		for (int i = 2; i <= n; ++i) {
			d[v[i]] = g[v[1]][v[i]];
			if (d[v[i]] > d[v[p]]) p = i;
		}
		vis[v[1]] = n;
		for (int i = 2; i <= n; ++i) {
			if (i == n) {
				res = min(res, d[v[p]]); // if d[v[p]] < res, then s = v[p] & t = v[prev]
				for (int j = 1; j <= n; ++j) {
					g[v[prev]][v[j]] += g[v[p]][v[j]];
					g[v[j]][v[prev]] = g[v[prev]][v[j]];
				}
				v[p] = v[n--];
				break;
			}
			vis[v[p]] = n;
			prev = p;
			p = -1;
			for (int j = 2; j <= n; ++j) {
				if (vis[v[j]] != n) {
					d[v[j]] += g[v[prev]][v[j]];
					if (p == -1 || d[v[p]] < d[v[j]]) p = j;
				}
			}
		}
	}
	return res;
}