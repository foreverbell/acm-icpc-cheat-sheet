int n, m, s, t, ec, d[maxn]; // Minimum cost, maximum flow(ZKW version), t=n
struct edge_link {
	int v, r, w;
	edge_link *next, *pair;
} edge[maxm], *header[maxn];
bool vis[maxn];
void add(int u, int v, int r, int w) // (u, v, r, w), (v, u, 0, -w)

void spfa() {
	queue<int> q;
	for (int i = 1; i <= t; ++i) d[i] = maxint, vis[i] = false;
	d[s] = 0, q.push(s), vis[s] = true;
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = false;
		for (edge_link *e = header[u]; e != NULL; e = e->next) {
			if (e->r && d[u] + e->w < d[e->v]) {
				d[e->v] = d[u] + e->w;
				if (!vis[e->v]) q.push(e->v), vis[e->v] = true;
			}
		}
	}
	for (int i = 1; i <= t; ++i) d[i] = d[t] - d[i];
}

int augment(int u, int flow) {
	if (u == t) return flow;
	vis[u] = true;
	for (edge_link *e = header[u]; e != NULL; e = e->next) {
		if (e->r && !vis[e->v] && d[e->v] + e->w == d[u]) {
			int temp = augment(e->v, min(flow, e->r));
			if (temp) {
				e->r -= temp, e->pair->r += temp;
				return temp;
			}
		}
	}
	return 0;
}

bool adjust() {
	int delta = maxint;
	for (int u = 1; u <= t; ++u) {
		if (!vis[u]) continue;
		for (edge_link *e = header[u]; e != NULL; e = e->next) {
			if (e->r && !vis[e->v] && d[e->v] + e->w > d[u]) {
				delta = min(delta, d[e->v] + e->w - d[u]);
			}
		}
	}
	if (delta == maxint) return false;
	for (int i = 1; i <= t; ++i) {
		if (vis[i]) d[i] += delta;
	}
	memset(vis, 0, sizeof(vis));
	return true;
}

pair<int, int> cost_flow() {
	int temp, flow = 0, cost = 0;
	spfa();
	do {
		while (temp = augment(s, maxint)) {
			flow += temp;
			memset(vis, 0, sizeof(vis));
		}
	} while (adjust());
	for (int i = 2; i <= ec; i += 2) cost += edge[i].r * edge[i - 1].w;
	return make_pair(flow, cost);
}