void curve_fit(const vector<pair<double, double> > &data, int n) { // a*x^n+b*x^n-1+...+1*?=second
	double g[N][N]; memset(g, 0, sizeof(g));
	for (int i = n; i >= 0; --i) {
		for (int j = 0; j <= n; ++j) {
			g[j + 1][n - i + 1] = pow(data[j].first, i);
		}
	}
	for (int j = 0; j <= n; ++j) g[j + 1][n + 2] = data[j].second;
	gauss(n + 1, g);
	vector<double> f(n + 1);
	for (int i = 1; i <= n + 1; ++i) {
		for (int j = 1; j <= n + 1; ++j) {
			if (fabs(g[i][j] - 1) < 1e-8) {
				f[n - j + 1] = g[i][n + 2];
				break;
			}
		}
	}
	for (int i = n; i >= 1; --i) printf("%.5lf x^%d + ", f[i], i);
	printf("%.5lf\n", f[0]);
	for (int i = 0; i < data.size(); ++i) {
		double x = data[i].first, val = data[i].second;
		for (int j = n; j >= 0; --j) val -= pow(x, j) * f[j];
		if (fabs(val) > 1e-8) { puts("fail"); return; }
	} puts("ok");
}