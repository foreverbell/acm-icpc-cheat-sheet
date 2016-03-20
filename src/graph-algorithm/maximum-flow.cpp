struct networkFlow {
  struct edge_t {
    int v, r, next;
    edge_t(int v, int r, int next) : v(v), r(r), next(next) { }
  };
  vector<edge_t> edges;
  int s, t, n, h[maxN], d[maxN], vd[maxN], cur[maxN];

  void clear() {
    edges.clear(); mset(h, -1);
  }

  void add(int u, int v, int r) {
    int ec = (int) edges.size();
    edges.push_back(edge_t(v, r, h[u]));
    h[u] = edges.size() - 1;
    edges.push_back(edge_t(u, 0, h[v]));
    h[v] = edges.size() - 1;
  }

  int augment(int u, int flow) {
    if (u == t) return flow;
    int temp, res = 0;
    for (int &e = cur[u]; e != -1; e = edges[e].next) {
      int v = edges[e].v, r = edges[e].r;
      if (r && d[u] == d[v] + 1) {
        temp = augment(v, min(r, flow - res));
        edges[e].r -= temp, edges[e ^ 1].r += temp, res += temp;
        if (d[s] == n || res == flow) return res;
      }
    }
    if (--vd[d[u]] == 0) d[s] = n;
    else cur[u] = h[u], ++vd[++d[u]];
    return res;
  }

  int flow(int s, int t, int n) {
    int f = 0;
    mset0(d); mset0(vd);
    this->s = s, this->t = t, this->n = n;
    vd[0] = n;
    for (int i = 1; i <= n; ++i) cur[i] = h[i];
    while (d[s] < n) f += augment(s, maxint);
    return f;
  }
};