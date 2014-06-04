int minkowski(point_t *h, point_t *h1, point_t *h2, int n, int m) {
	point_t c = point_t(0, 0);
	for (int i = 1; i <= m; ++i) c = c + h2[i];
	c = c / m;
	for (int i = 1; i <= m; ++i) h2[i] = h2[i] - c;
	int cur = -1;
	for (int i = 1; i <= m; ++i) {
		if (dblcmp(cross(h2[i], h1[1] - h1[n])) >= 0) {
			if (cur == -1 || cross(h2[i], h1[1] - h1[n]) > cross(h2[cur], h1[1] - h1[n])) cur = i;
		}
	}
	int cnt = 0;
	h1[n + 1] = h1[1];
	for (int i = 1; i <= n; ++i) {
		while (true) {
			h[++cnt] = h1[i] + h2[cur];
			int next = (cur == m ? 1 : cur + 1);
			if (dblcmp(cross(h2[cur], h1[i + 1] - h1[i])) < 0) cur = next;
			else {
				if (cross(h2[next], h1[i + 1] - h1[i]) > cross(h2[cur], h1[i + 1] - h1[i])) cur = next;
				else break;
			}
		}
	}
	for (int i = 1; i <= cnt; ++i) h[i] = h[i] + c;
	for (int i = 1; i <= m; ++i) h2[i] = h2[i] + c;
	return graham(h, cnt);
}