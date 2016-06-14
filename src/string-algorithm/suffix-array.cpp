const int maxN = 100002, logN = 21, maxint = 0x7f7f7f7f;
int n, sa[maxN], r[maxN + maxN], h[maxN], mv[maxN][logN], _lg[maxN];
// r is `doubled`
void initlg() {
  _lg[1] = 0;
  for (int i = 2; i < maxN; ++i) _lg[i] = _lg[i - 1] + ((i & (i - 1)) == 0 ? 1 : 0);
}
// remember to clear r & call initlg() before calling
void construct(int n, int *s) { // initlg();
  static pair<int/* Type */, int> ord[maxN];
  for (int i = 1; i <= n; ++i) ord[i] = make_pair(s[i], i);
  sort(ord + 1, ord + 1 + n);
  for (int i = 1; i <= n; ++i) {
    sa[i] = ord[i].second;
    r[sa[i]] = (i == 1 ? 1 : r[sa[i - 1]] + (ord[i - 1].first != ord[i].first));
  }
  static int tr[maxN], tsa[maxN], c[maxN];
  for (int l = 1; l < n; l <<= 1) {
    int cnt = 0;
    for (int i = 1; i <= n; ++i) if (sa[i] + l > n) tsa[++cnt] = sa[i];
    for (int i = 1; i <= n; ++i) if (sa[i] > l) tsa[++cnt] = sa[i] - l;
    mset0(c);
    for (int i = 1; i <= n; ++i) ++c[r[i]];
    for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
    for (int i = n; i >= 1; --i) sa[c[r[tsa[i]]]--] = tsa[i];
    tr[sa[1]] = 1;
    for (int i = 2; i <= n; ++i) {
      tr[sa[i]] = tr[sa[i - 1]] + (r[sa[i]] != r[sa[i - 1]] || r[sa[i] + l] != r[sa[i - 1] + l]);
    }
    for (int i = 1; i <= n; ++i) r[i] = tr[i];
    if (r[sa[n]] == n) break;
  }
  int k = 0; /* Height && RMQ */
  for (int i = 1; i <= n; ++i) {
    if (--k < 0) k = 0;
    for (int j = sa[r[i] - 1]; r[i] != 1 && s[i + k] == s[j + k]; ++k);
    h[r[i]] = k;
  }
  for (int i = 1; i <= n; ++i) mv[i][0] = h[i];
  for (int k = 1; k < logN; ++k) {
    for (int i = 1, len = 1 << (k - 1); i + len <= n; ++i) {
      mv[i][k] = min(mv[i][k - 1], mv[i + len][k - 1]);
    }
  }
}

int askRMQ(int l, int r) {
  int len = r - l + 1, log = _lg[r - l + 1];
  return min(mv[l][log], mv[r - (1 << log) + 1][log]);
}

int LCP(int i, int j) {
  i = r[i], j = r[j];
  if (i > j) swap(i, j);
  return askRMQ(++i, j);
}
