int n, ec, ID[maxn], pre[maxn], in[maxn], vis[maxn];
struct edge_t {
	int u, v, w;
} edge[maxm];
void add(int u, int v, int w) {
	edge[++ec].u = u, edge[ec].v = v, edge[ec].w = w;
}

int arborescence(int n, int root) {
	int res = 0, index;
	while (true) {
		for (int i = 1; i <= n; ++i) {
			in[i] = maxint, vis[i] = -1, ID[i] = -1;
		}
		for (int i = 1; i <= ec; ++i) {
			int u = edge[i].u, v = edge[i].v;
			if (u == v || in[v] <= edge[i].w) continue;
			in[v] = edge[i].w, pre[v] = u;
		}
		pre[root] = root, in[root] = 0;
		for (int i = 1; i <= n; ++i) {
			res += in[i];
			if (in[i] == maxint) return -1;
		}
		index = 0;
		for (int i = 1; i <= n; ++i) {
			if (vis[i] != -1) continue;
			int u = i, v;
			while (vis[u] == -1) {
				vis[u] = i;
				u = pre[u];
			}
			if (vis[u] != i || u == root) continue;
			for (v = u, u = pre[u], ++index; u != v; u = pre[u]) ID[u] = index;
			ID[v] = index;
		}
		if (index == 0) return res;
		for (int i = 1; i <= n; ++i) if (ID[i] == -1) ID[i] = ++index;
		for (int i = 1; i <= ec; ++i) {
			int u = edge[i].u, v = edge[i].v;
			edge[i].u = ID[u], edge[i].v = ID[v];
			edge[i].w -= in[v];
		}
		n = index, root = ID[root];
	}
	return res;
}