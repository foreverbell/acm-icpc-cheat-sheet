double dac(point_t *p, int l, int r) {
  double d = 10e100;
  if (r - l <= 3) {
    for (int i = l; i <= r; ++i) {
      for (int j = i + 1; j <= r; ++j) {
        d = min(d, dist2(p[i], p[j]));
      }
    }
    sort(p + l, p + r + 1, cmpY);
  } else {
    int mid = (l + r) / 2;
    d = min(dac(p, l, mid), dac(p, mid + 1, r));
    inplace_merge(p + l, p + mid + 1, p + r + 1, cmpY);
    static point_t tmp[maxn]; int cnt = 0;
    for (int i = l; i <= r; ++i) {
      if ((p[i].x - p[mid].x) * (p[i].x - p[mid].x) <= d) tmp[++cnt] = p[i];
    }
    for (int i = 1; i <= cnt; ++i) {
      for (int j = 1; j <= 8 && j + i <= cnt; ++j) {
        d = min(d, dist2(tmp[i], tmp[j + i]));
      }
    }
  }
  return d;
}

double cal(point_t *p, int n) {
  sort(p + 1, p + 1 + n, cmpX);
  return sqrt(dac(p, 1, n));
}