// O(N^2) sol, polygon counterclockwise order
// i.e., left side of vector v1->v2 is the valid half plane
const double maxd = 1e5;
int n, cnt;
point_t p[maxn];

void init() { // order reversed if right side
	cnt = 4;
	p[1] = point_t(-maxd, -maxd);
	p[2] = point_t(maxd, -maxd);
	p[3] = point_t(maxd, maxd);
	p[4] = point_t(-maxd, maxd);
}

void cut(point_t p1, point_t p2) {
	int tcnt = 0;
	static point_t tp[maxn];
	p[cnt + 1] = p[1];
	for (int i = 1; i <= cnt; ++i) {
		double v1 = cross(p2 - p1, p[i] - p1);
		double v2 = cross(p2 - p1, p[i + 1] - p1);
		if (dblcmp(v1) >= 0) tp[++tcnt] = p[i]; // <= if right side
		if (dblcmp(v1) * dblcmp(v2) < 0) tp[++tcnt] = isLL(p1, p2, p[i], p[i + 1]);		
	}
	cnt = tcnt;
	for (int i = 1; i <= cnt; ++i) p[i] = tp[i];
}