int bk, size[maxn], parent[maxn], ver[maxn];
bool cut[maxn];

void bfs(int r) { // bfs in each sub-tree
  parent[r] = 0, bk = 0; // maintain root extra information
  static queue<int> Q; static stack<int> U;
  Q.push(r);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop(); U.push(u);
    size[u] = 1, ver[++bk] = u; // find a node in sub-tree
    for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
      int v = *it;
      if (v == parent[u] || cut[v]) continue;
      parent[v] = u; // maintain v from u
      Q.push(v);
    }
  }
  while (!U.empty()) {
    int u = U.top(); U.pop();
    if (parent[u]) size[parent[u]] += size[u];
  }
}

int findCentre(int r) {
  static queue<int> Q;
  int result = 0, rsize = maxint;
  bfs(r);
  Q.push(r);
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();
    int temp = size[r] - size[u];
    for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
      int v = *it;
      if (cut[v] || v == parent[u]) continue;
      temp = max(temp, size[v]);
      Q.push(v);
    }
    if (temp < rsize) rsize = temp, result = u;
  }
  return result;
}

int work(int u) {
  int result = 0;
  u = findCentre(u);
  cut[u] = true;
  for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
    int v = *it;
    if (!cut[v]) /*result += */work(v); // process each sub-tree
  }
  for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
    int v = *it;
    if (cut[v]) continue;
    bfs(v); // then combine sub-trees
  }
  cut[u] = false;
  return result;
}