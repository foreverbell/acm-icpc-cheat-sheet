// Calculate the maximum distance of a point set.
double rotate_caliper() {
  p[0] = p[n];
  int to = 0;
  double ans = 0;
  for (int i = 0; i < n; ++i) {
    while ((to + 1) % n != i) {
      if (dblcmp(cross(p[i + 1] - p[i], p[to + 1] - p[i]) - cross(p[i + 1] - p[i], p[to] - p[i])) >= 0) to = (to + 1) % n;
      else break;
    }
    ans = max(ans, dist(p[i], p[to]));
    ans = max(ans, dist(p[i + 1], p[to]));
  }
  return ans;
}
