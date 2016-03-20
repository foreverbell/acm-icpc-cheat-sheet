int parent[maxN], label[maxN], cnt, who[maxN];
int semi[maxN], idom[maxN], ancestor[maxN], best[maxN];
vector<int> edge[maxN], succ[maxN], pred[maxN];
deque<int> bucket[maxN];

void dfs(int u) {
  label[u] = ++cnt; who[cnt] = u;
  for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
    int v = *it;
    if (v == parent[u] || label[v] != -1) continue;
    parent[v] = u;
    dfs(v);
  }
}

void link(int v, int w) {
  ancestor[w] = v;
}

void compress(int v) {
  int a = ancestor[v];
  if (ancestor[a] == 0) return;
  compress(a);
  if (semi[best[v]] > semi[best[a]]) best[v] = best[a];
  ancestor[v] = ancestor[a];
}

int eval(int v) {
  if (ancestor[v] == 0) return v;
  compress(v);
  return best[v];
}

void dominator() {
  cnt = 0;
  for (int i = 1; i <= n; ++i) {
    label[i] = -1;
    succ[i].clear(), pred[i].clear();
  }
  dfs(n); // n is root
  for (int u = 1; u <= n; ++u) {
    for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
      int v = *it;
      if (label[u] != -1 && label[v] != -1) {
        succ[label[u]].push_back(label[v]);
        pred[label[v]].push_back(label[u]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    semi[i] = best[i] = i;
    idom[i] = ancestor[i] = 0;
    bucket[i].clear();
  }
  for (int w = cnt; w >= 2; --w) {
    int p = label[parent[who[w]]];
    for (vector<int>::iterator it = pred[w].begin(); it != pred[w].end(); ++it) {
      int v = *it;
      int u = eval(v);
      if (semi[w] > semi[u]) semi[w] = semi[u];
    }
    bucket[semi[w]].push_back(w);
    link(p, w);
    while (!bucket[p].empty()) {
      int v = bucket[p].front();
      bucket[p].pop_front();
      int u = eval(v);
      idom[v] = (semi[u] < p ? u : p);
    }
  }
  for (int w = 2; w <= cnt; ++w) {
    if (idom[w] != semi[w]) idom[w] = idom[idom[w]];
  }
  idom[1] = 0;
  for (int i = 1; i <= cnt; ++i) {
    int u = who[idom[i]], v = who[i];
    // u is immediate dominator of v (i == 1?)
  }
}
