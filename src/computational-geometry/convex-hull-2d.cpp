bool cmp(const point_t p1, const point_t p2) {
  return dblcmp(p1.y - p2.y) == 0 ? p1.x < p2.x : p1.y < p2.y;
}

int graham(point_t *p) { // Points co-lined are ignored.
  int top = 2; static point_t sk[maxn];
  sort(p + 1, p + 1 + n, cmp); 
  sk[1] = p[1], sk[2] = p[2];
  for (int i = 3; i <= n; ++i) {
    while (top >= 2 && dblcmp(cross(p[i] - sk[top - 1], sk[top] - sk[top - 1])) >= 0) --top;
    sk[++top] = p[i];
  }
  int ttop = top;
  for (int i = n - 1; i >= 1; --i) {
    while (top > ttop && dblcmp(cross(p[i] - sk[top - 1], sk[top] - sk[top - 1])) >= 0) --top;
    sk[++top] = p[i];
  }
  for (int i = 1; i < top; ++i) p[i] = sk[i];
  return --top;
}
