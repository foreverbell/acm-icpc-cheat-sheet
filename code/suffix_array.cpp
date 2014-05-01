const int maxn = 100002, logn = 21, maxint = 0x7f7f7f7f;
int n, sa[maxn], r[maxn], h[maxn], mv[maxn][logn];

void construct(int n, int *s) { // remember to clear s before calling
	static pair<int/* Type */, int> ord[maxn];
	for (int i = 1; i <= n; ++i) ord[i] = make_pair(s[i], i);
	sort(ord + 1, ord + 1 + n);
	for (int i = 1; i <= n; ++i) {
		sa[i] = ord[i].second;
		r[sa[i]] = (i == 1 ? 1 : r[sa[i - 1]] + (ord[i - 1].first != ord[i].first));
	}
	static int tr[2][maxn], tsa[maxn], c[maxn];
	for (int l = 1; l < n; l <<= 1) {
		for (int i = 1; i <= n; ++i) {
			tr[0][i] = r[i], tr[1][i] = (i + l <= n ? r[i + l] : 0);
		}
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) ++c[tr[1][i]];
		for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) tsa[c[tr[1][i]]--] = i;
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) ++c[tr[0][i]];
		for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[tr[0][tsa[i]]]--] = tsa[i];
		r[sa[1]] = 1;
		for (int i = 2; i <= n; ++i) {
			r[sa[i]] = r[sa[i - 1]] + (tr[0][sa[i]] != tr[0][sa[i - 1]] || tr[1][sa[i]] != tr[1][sa[i - 1]]);
		}
	}
	int k = 0; /* Height && RMQ */
	for (int i = 1; i <= n; ++i) {
		if (--k < 0) k = 0;
		for (int j = sa[r[i] - 1]; r[i] != 1 && s[i + k] == s[j + k]; ++k);
		h[r[i]] = k;
	}
	for (int i = 1; i <= n; ++i) mv[i][0] = h[i];
	for (int k = 1; k < logn; ++k) {
		for (int i = 1; i + (1 << (k - 1)) <= n; ++i) {
			mv[i][k] = min(mv[i][k - 1], mv[i + (1 << (k - 1))][k - 1]);
		}
	}
}

int askRMQ(int l, int r) {
	int res = maxint, len = r - l + 1;
	for (int k = logn - 1; k >= 0; --k) {
		if (len & (1 << k)) {
			res = min(res, mv[l][k]);
			l += (len & (1 << k));
		}
	}
	return res;
}

int LCP(int i, int j) {
	i = r[i], j = r[j];
	if (i > j) swap(i, j);
	return askRMQ(++i, j);
}