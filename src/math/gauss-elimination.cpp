void eliminate(int n, double g[maxN][maxN]) { // n*(n+1), Ax=b
  for (int i = 1; i <= n; ++i) {
    double temp = 0;
    int pos = -1;
    for (int j = i; j <= n; ++j) {
      if (fabs(g[j][i]) > temp) temp = fabs(g[j][i]), pos = j;
    }
    if (pos == -1) continue;
    for (int k = 1; k <= n + 1; ++k) swap(g[pos][k], g[i][k]);
    temp = g[i][i];
    for (int k = 1; k <= n + 1; ++k) g[i][k] /= temp;
    for (int j = i + 1; j <= n; ++j) {
      temp = g[j][i];
      for (int k = 1; k <= n + 1; ++k) g[j][k] -= temp * g[i][k];
    }
  }
  for (int i = n; i >= 1; --i) {
    for (int j = 1; j < i; ++j) {
      g[j][n + 1] -= g[i][n + 1] * g[j][i];
      g[j][i] = 0;
    }
  }
}