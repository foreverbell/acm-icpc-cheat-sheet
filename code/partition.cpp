// number of ways to divide n to integers(unordered), O(n^(3/2))
int partition(int n) {
	int dp[n + 1];
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		dp[i] = 0;
		for (int j = 1, r = 1; i - (3 * j * j - j) / 2 >= 0; ++j, r *= -1) {
			dp[i] += dp[i - (3 * j * j - j) / 2] * r;
			if (i - (3 * j * j + j) / 2 >= 0) dp[i] += dp[i - (3 * j * j + j) / 2] * r;
		}
	}
	return dp[n];
}