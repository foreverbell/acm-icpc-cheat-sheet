// Complexity: Q*N^0.5 * O(add)
int sqrtN = int(sqrt(double(q)));
sort(Q + 1, Q + 1 + q, cmpL);
for (int i = 1; i <= q; i += sqrtN) {
  clear();
  int begin = i, end = i + sqrtN - 1;
  if (end > q) end = q;
  sort(Q + begin, Q + end + 1, cmpR);
  Q[begin - 1].l = 1, Q[begin - 1].r = 0;
  for (int j = begin; j <= end; ++j) {
    for (int k = Q[j - 1].r + 1; k <= Q[j].r; ++k) add(k, 1);
    if (Q[j].l > Q[j - 1].l) {
      for (int k = Q[j - 1].l; k < Q[j].l; ++k) add(k, -1);
    } else if (Q[j].l < Q[j - 1].l) {
      for (int k = Q[j].l; k < Q[j - 1].l; ++k) add(k, 1);
    }
    ans[Q[j].ID] = res;
  }
}
