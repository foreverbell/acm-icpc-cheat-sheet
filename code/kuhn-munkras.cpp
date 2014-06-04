// Kuhn-Munkras's algorithm, maxn: Left Size; maxm: Right Size.
int n, m, g[maxn][maxm], lx[maxn], ly[maxm], slack[maxm], match[maxm];
bool vx[maxn], vy[maxm];

bool find(int x) {
	vx[x] = true;
	for (int y = 1; y <= m; ++y) {
		if (!vy[y]) {
			int delta = lx[x] + ly[y] - g[x][y];
			if (delta == 0) {
				vy[y] = true;
				if (match[y] == 0 || find(match[y])) {
					match[y] = x;
					return true;
				}
			} else slack[y] = min(slack[y], delta);
		}
	}
	return false;
}

int km() { // #define sm(p, f) memset((p), f, sizeof(p))
	// maximum weight, if minimum, negate all g then restore at the end.
	sm(lx, 0x80), sm(ly, 0), sm(match, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) lx[i] = max(lx[i], g[i][j]);
	}
	for (int k = 1; k <= n; ++k) {
		sm(slack, 0x7f);
		while (true) {
			sm(vx, 0), sm(vy, 0);
			if (find(k)) break;
			else {
				int delta = maxint;
				for (int i = 1; i <= m; ++i) {
					if (!vy[i]) delta = min(delta, slack[i]);
				}
				for (int i = 1; i <= n; ++i) {
					if (vx[i]) lx[i] -= delta;
				}
				for (int i = 1; i <= m; ++i) {
					if (vy[i]) ly[i] += delta;
					if (!vy[i]) slack[i] -= delta;
				}
			}
		}
	}
	int result = 0;
	for (int i = 1; i <= n; ++i) result += lx[i];
	for (int i = 1; i <= m; ++i) result += ly[i];
	return result;
}