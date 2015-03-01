// Accuracy is not guaranteed.
double cal(const vector<double> &coef, double x) {
	double e = 1, s = 0;
	for (int i = 0; i < coef.size(); ++i) s += coef[i] * e, e *= x;
	return s;
}

double newton(const vector<double> &coef, const vector<double> &dcoef, double l, double r, int sl, int sr) {
	double x = (l + r) / 2;
	for (int i = 0; i < 7; ++i) {
		double y = x - cal(coef, x) / cal(dcoef, x) / coef.size();
		if (dblcmp(cal(coef, y)) == 0 || dblcmp(x - y) == 0) return y;
		x = y;
	}
	if (dblcmp(cal(coef, x)) == 0) return x;
	for (int it = 0; it < 32 && dblcmp(r - l) != 0; ++it) {
		double mid = (l + r) / 2;
		int smid = dblcmp(cal(coef, mid));
		if (smid == 0) return mid;
		else if (sl * smid < 0) r = mid;
		else l = mid;
	}
	return (l + r) / 2;
}

void rec(const vector<double> &coef, vector<vector<double>> &roots, int n) {
	vector<double> ret, dcoef(n);
	for (int i = 0; i < n; ++i) dcoef[i] = coef[i + 1] * (i + 1) / n;
	if (n == 1) {
		ret.push_back(-coef[0]);
	} else if (n == 2) {
		rec(dcoef, roots, 1);
		double b = coef[1], c = coef[0];
		double d = b * b - 4 * c;
		if (d >= 0) {
			d = sqrt(d);
			ret.push_back((-b - d) / 2);
			ret.push_back((-b + d) / 2);
		}
	} else {
		rec(dcoef, roots, n - 1);
		vector<double> droot = roots[n - 1], ddroot = roots[n - 2];
		double b = 1;
		for (int i = 0; i <= n; ++i) b = max(b, pow(fabs(coef[i]), 1.0 / (n - i)));
		b *= 2;
		droot.insert(droot.begin(), -b);
		droot.push_back(b);
		int p = 0;
		for (int i = 0; i + 1 < droot.size(); ++i) {
			double l = droot[i], r = droot[i + 1];
			int sl = dblcmp(cal(coef, l)), sr = dblcmp(cal(coef, r));
			if (sl * sr > 0) continue;
			else if (sl == 0) ret.push_back(l);
			else if (sr == 0) ret.push_back(r);
			else {
				while (p < ddroot.size() && ddroot[p] < l) ++p;
				while (p < ddroot.size() && ddroot[p] <= r) {
					int s = dblcmp(cal(coef, ddroot[p]));
					if (s == 0) {
						l = r = ddroot[p];
						break;
					} else if (s * sl > 0) {
						l = ddroot[p];
					} else {
						r = ddroot[p];
						break;
					}
					++p;
				}
				if (dblcmp(r - l) == 0) ret.push_back(l);
				else ret.push_back(newton(coef, dcoef, l, r, sl, sr));
			}
		}
	}
	roots[n] = ret;
}

vector<double> solve(vector<double> coef) {
	int n = coef.size() - 1;
	while (coef.back() == 0) coef.pop_back(), --n;
	for (int i = 0; i <= n; ++i) coef[i] /= coef[n];
	vector<vector<double>> roots(n + 1);
	rec(coef, roots, n);
	return roots[n];
}