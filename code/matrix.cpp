struct matrix_t {
	int x[N + 1][N + 1];
	matrix_t(int v) {
		memset(x, 0, sizeof(x));
		for (int i = 1; i <= N; ++i) x[i][i] = v;
	}
	matrix_t operator*(const matrix_t &r) {
		matrix_t p = 0;
		for (int k = 1; k <= N; ++k) {
			for (int i = 1; i <= N; ++i) {
				if (x[i][k] == 0) continue;
				for (int j = 1; j <= N; ++j) {
					p.x[i][j] += x[i][k] * r.x[k][j];
					p.x[i][j] %= MOD;
				}
			}
		}
		return p;
	}
	matrix_t power(LL p) {
		matrix_t r = 1, a = *this;
		for (; p; p >>= 1) {
			if (p & 1) r = r * a;
			a = a * a;
		}
		return r;
	}
};