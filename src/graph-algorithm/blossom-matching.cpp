int n, match[maxN], pre[maxN], base[maxN]; 
bool inQ[maxN], inB[maxN], inP[maxN];
queue<int> Q;
vector<int> edge[maxN];

int LCA(int u, int v) {
  for (int i = 1; i <= n; ++i) inP[i] = false;
  while (true) {
    u = base[u];
    inP[u] = true;
    if (match[u] == -1) break;
    u = pre[match[u]];
  }
  while (true) {
    v = base[v];
    if (inP[v]) return v;
    v = pre[match[v]];
  }
}

void reset(int u, int a) {
  while (u != a) {
    int v = match[u];
    inB[base[u]] = inB[base[v]] = true;
    v = pre[v];
    if (base[v] != a) pre[v] = match[u];
    u = v;
  }
}

void contract(int u, int v) {
  int a = LCA(u, v);
  for (int i = 1; i <= n; ++i) inB[i] = false;
  reset(u, a), reset(v, a);
  if (base[u] != a) pre[u] = v;
  if (base[v] != a) pre[v] = u;
  for (int i = 1; i <= n; ++i) {
    if (!inB[base[i]]) continue;
    base[i] = a;
    if (!inQ[i]) Q.push(i), inQ[i] = true;
  }
}

bool dfs(int s) {
  for (int i = 1; i <= n; ++i) pre[i] = -1, inQ[i] = false, base[i] = i;
  while (!Q.empty()) Q.pop();
  Q.push(s), inQ[s] = true;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
      int v = *it;
      if (base[u] == base[v] || match[u] == v) continue;
      if (v == s || (match[v] != -1 && pre[match[v]] != -1)) contract(u, v);
      else if (pre[v] == -1) {
        pre[v] = u;
        if (match[v] != -1) {
          Q.push(match[v]), inQ[match[v]] = true;
        } else {
          u = v;
          while (u != -1) {
            v = pre[u];
            int w = match[v];
            match[u] = v, match[v] = u;
            u = w;
          }
          return true;
        }
      }
    }
  }
  return false;
}

int blossom() {
  int ans = 0;
  for (int i = 1; i <= n; ++i) match[i] = -1;
  for (int i = 1; i <= n; ++i) {
    if (match[i] == -1 && dfs(i)) ++ans;
  }
  return ans;
}