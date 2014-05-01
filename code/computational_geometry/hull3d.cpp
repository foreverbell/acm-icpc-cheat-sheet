int n, bf[maxn][maxn], fcnt;
point_t pt[maxn];
struct face_t {
	int a, b, c;
	bool vis;
} fc[maxn << 5]; /* Number of Faces(Unknown) */

bool remove(int p, int b, int a) {
	int f = bf[b][a];
	face_t ff;
	if (fc[f].vis) {
		if (dblcmp(volume(pt[p], pt[fc[f].a], pt[fc[f].b], pt[fc[f].c])) >= 0) {
			return true;
		} else {
			ff.a = a, ff.b = b, ff.c = p;
			bf[ff.a][ff.b] = bf[ff.b][ff.c] = bf[ff.c][ff.a] = ++fcnt;
			ff.vis = true;
			fc[fcnt] = ff;
		}
	}
	return false;
}

void dfs(int p, int f) {
	fc[f].vis = false;
	if (remove(p, fc[f].b, fc[f].a)) dfs(p, bf[fc[f].b][fc[f].a]);
	if (remove(p, fc[f].c, fc[f].b)) dfs(p, bf[fc[f].c][fc[f].b]);
	if (remove(p, fc[f].a, fc[f].c)) dfs(p, bf[fc[f].a][fc[f].c]);
}

void hull3d() {
	for (int i = 2; i <= n; ++i) {
		if (dblcmp((pt[i] - pt[1]).length()) > 0) swap(pt[i], pt[2]);
	}
	for (int i = 3; i <= n; ++i) {
		if (dblcmp(fabs(area(pt[1], pt[2], pt[i]))) > 0) swap(pt[i], pt[3]);
	}
	for (int i = 4; i <= n; ++i) {
		if (dblcmp(fabs(volume(pt[1], pt[2], pt[3], pt[i]))) > 0) swap(pt[i], pt[4]);
	}
	zm(fc), fcnt = 0, zm(bf);
	for (int i = 1; i <= 4; ++i) {
		face_t f;
		f.a = i + 1, f.b = i + 2, f.c = i + 3;
		if (f.a > 4) f.a -= 4;
		if (f.b > 4) f.b -= 4;
		if (f.c > 4) f.c -= 4;
		if (dblcmp(volume(pt[i], pt[f.a], pt[f.b], pt[f.c])) > 0) swap(f.a, f.b);
		f.vis = true;
		bf[f.a][f.b] = bf[f.b][f.c] = bf[f.c][f.a] = ++fcnt;
		fc[fcnt] = f;
	}
	random_shuffle(pt + 5, pt + 1 + n);
	for (int i = 5; i <= n; ++i) {
		for (int j = 1; j <= fcnt; ++j) {
			if (!fc[j].vis) continue;
			if (dblcmp(volume(pt[i], pt[fc[j].a], pt[fc[j].b], pt[fc[j].c])) >= 0) {
				dfs(i, j);
				break;
			}
		}
	}
	for (int i = 1; i <= fcnt; ++i) if (!fc[i].vis) swap(fc[i--], fc[fcnt--]);
}