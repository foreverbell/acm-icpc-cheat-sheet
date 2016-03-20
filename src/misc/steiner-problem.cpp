// Steiner's Problem: ts[m], list of vertices to be united, indexed from 0.
int steiner(int *ts, int m) { // O(3^m*n+2^m*n^2+n^3)
  floyd();
  memset(dp, 0, sizeof(dp));
  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= n; ++j) {
      dp[1 << i][j] = g[ts[i]][j];
    }
  }
  for (int i = 1; i < (1 << m); ++i) {
    if (((i - 1) & i) != 0) {
      for (int j = 1; j <= n; ++j) {
        dp[i][j] = maxint;
        for (int k = (i - 1) & i; k > 0; k = (k - 1) & i) {
          dp[i][j] = min(dp[i][j], dp[k][j] + dp[i ^ k][j]);
        }
      }
      for (int j = 1; j <= n; ++j) {
        for (int k = 1; k <= n; ++k) {
          dp[i][j] = min(dp[i][j], dp[i][k] + g[k][j]);
        }
      }
    }
  }
  return dp[(1 << m) - 1][ts[0]];
}