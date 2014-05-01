/* Self-adjust simpson */
const double eps = 1e-15; // as small as possible
double f(double x) { return 0.0; }

double sim(double l, double r, double lv, double rv, double mv) {
	return (r - l) * (lv + rv + 4 * mv) / 6;
}

double rsim(double l, double r, double lv, double rv, double mv, double m1v, double m2v) {
	double mid = (l + r) / 2;
	if (fabs(sim(l, r, lv, rv, mv) - sim(l, mid, lv, mv, m1v) - sim(mid, r, mv, rv, m2v)) / 15 < eps) {
		return sim(l, r, lv, rv, mv);
	} else {
		double mid = (l + r) / 2, m1 = (l + (l + r) / 2) / 2, m2 = ((l + r) / 2 + r) / 2;
		return rsim(l, mid, lv, mv, m1v, f((l + m1) / 2), f((m1 + mid) / 2)) + rsim(mid, r, mv, rv, m2v, f((mid + m2) / 2), f((m2 + r) / 2));
	}
}

double simpson(double l, double r) {
	double mid = (l + r) / 2;
	return rsim(l, r, f(l), f(r), f(mid), f((l + mid) / 2), f((mid + r) / 2));
}