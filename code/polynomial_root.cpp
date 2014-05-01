double cal(const vector<double> &coef, double x) {
	double e = 1, s = 0;
	for (int i = 0; i < coef.size(); ++i) s += coef[i] * e, e *= x;
	return s;
}

double find(const vector<double> &coef, double l, double r) {
	int sl = dblcmp(cal(coef, l)), sr = dblcmp(cal(coef, r));
	if (sl == 0) return l;
	if (sr == 0) return r;
	if (sl * sr > 0) return maxdbl;
	for (int tt = 0; tt < 100 && r - l > eps; ++tt) {
		double mid = (l + r) / 2;
		int smid = dblcmp(cal(coef, mid));
		if (smid == 0) return mid;
		if (sl * smid < 0) r = mid;
		else l = mid;
	}
	return (l + r) / 2;
}

vector<double> solve(vector<double> coef, int n) {
	vector<double> ret; // c[0]+c[1]*x+c[2]*x^2+...+c[n]*x^n
	if (n == 1) {
		if (dblcmp(coef[1]) != 0) ret.push_back(-coef[0] / coef[1]);
		return ret;
	}
	vector<double> dcoef(n);
	for (int i = 0; i < n; ++i) dcoef[i] = coef[i + 1] * (i + 1);
	vector<double> droot = solve(dcoef, n - 1);
	droot.insert(droot.begin(), -maxdbl);
	droot.push_back(maxdbl);
	for (int i = 0; i + 1 < droot.size(); ++i) {
		double tmp = find(coef, droot[i], droot[i + 1]);
		if (tmp < maxdbl) ret.push_back(tmp);
	}
	return ret;
}