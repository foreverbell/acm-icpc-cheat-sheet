double a[maxn][maxm], b[maxn], c[maxm], d[maxn][maxm];
int ix[maxn + maxm]; // !!! array all indexed from 0
// max{cx|Ax<=b,x>=0}, n: constraints, m: vars
double simplex(double a[maxn][maxm], double b[maxn], double c[maxm], int n, int m) {
	++m;
	int r = n, s = m - 1;
	memset(d, 0, sizeof(d));
	for (int i = 0; i < n + m; ++i) ix[i] = i;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m - 1; ++j) d[i][j] = -a[i][j];
		d[i][m - 1] = 1;
		d[i][m] = b[i];
		if (d[r][m] > d[i][m]) r = i;
	}
	for (int j = 0; j < m - 1; ++j) d[n][j] = c[j];
	d[n + 1][m - 1] = -1;
	for (double dd;; ) {
		if (r < n) {
			int t = ix[s]; ix[s] = ix[r + m]; ix[r + m] = t;
			d[r][s] = 1.0 / d[r][s];
			for (int j = 0; j <= m; ++j) if (j != s) d[r][j] *= -d[r][s];
			for (int i = 0; i <= n + 1; ++i) if (i != r) {
				for (int j = 0; j <= m; ++j) if (j != s) d[i][j] += d[r][j] * d[i][s];
				d[i][s] *= d[r][s];
			}
		}
		r = -1; s = -1;
		for (int j = 0; j < m; ++j) if (s < 0 || ix[s] > ix[j]) {
			if (d[n + 1][j] > eps || (d[n + 1][j] > -eps && d[n][j] > eps)) s = j;
		}
		if (s < 0) break;
		for (int i = 0; i < n; ++i) if (d[i][s] < -eps) {
			if (r < 0 || (dd = d[r][m] / d[r][s] - d[i][m] / d[i][s]) < -eps || (dd < eps && ix[r + m] > ix[i + m])) r = i;
		}
		if (r < 0) return -1; // not bounded
	}
	if (d[n + 1][m] < -eps) return -1; // not executable
	double ans = 0;
	for (int i = m; i < n + m; ++i) { // the missing enumerated x[i] = 0
		if (ix[i] < m - 1) ans += d[i - m][m] * c[ix[i]];
	}
	return ans;	
}