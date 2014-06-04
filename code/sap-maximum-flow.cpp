// assuming the sink has the maximum vertex ID => t = n
int n, m, s, t, ec, d[maxn], vd[maxn];
struct edge_link {
	int v, r;
	edge_link *next, *pair;
} edge[maxm], *header[maxn], *current[maxn];
void add(int u, int v, int r) // (u, v, r), (v, u, 0)

int augment(int u, int flow) {
	if (u == t) return flow;
	int temp, res = 0;
	for (edge_link *&e = current[u]; e != NULL; e = e->next) {
		if (e->r && d[u] == d[e->v] + 1) {
			temp = augment(e->v, min(e->r, flow - res));
			e->r -= temp, e->pair->r += temp, res += temp;
			if (d[s] == t || res == flow) return res;
		}
	}
	if (--vd[d[u]] == 0) d[s] = t;
	else current[u] = header[u], ++vd[++d[u]];
	return res;
}

int sap() {
	int flow = 0;
	memset(d, 0, sizeof(d)), memset(vd, 0, sizeof(vd));
	vd[0] = t;
	for (int i = 1; i <= t; ++i) current[i] = header[i];
	while (d[s] < t) flow += augment(s, maxint);
	return flow;
}