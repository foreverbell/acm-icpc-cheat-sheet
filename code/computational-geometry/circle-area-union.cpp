/* Circle Union, O(n^2logn) sol */
point_t center[maxn];
double radius[maxn], cntarea[maxn];

pair<double, double> isCC(point_t c1, point_t c2, double r1, double r2) {
	double d = dist(c1, c2);
	double x1 = c1.x, x2 = c2.x, y1 = c1.y, y2 = c2.y;
	double mid = atan2(y2 - y1, x2 - x1);
	double a = r1, c = r2;
	double t = acos((a * a + d * d - c * c) / (2 * a * d));
	return make_pair(mid - t, mid + t);
}

struct event_t {
	double theta;
	int delta;
	event_t(double t, int d) : theta(t), delta(d) { }
	bool operator<(const event_t &r) const {
		if (fabs(theta - r.theta) < eps) return delta > r.delta;
		return theta < r.theta;
	}
};
vector<event_t> e;

void add(double begin, double end) {
	if (begin <= -pi) begin += 2 * pi, end += 2 * pi;
	if (end > pi) {
		e.push_back(event_t(begin, 1));
		e.push_back(event_t(pi, -1));
		e.push_back(event_t(-pi, 1));
		e.push_back(event_t(end - 2 * pi, -1));
	} else {
		e.push_back(event_t(begin, 1));
		e.push_back(event_t(end, -1));
	}
}

double calc(point_t c, double r, double a1, double a2) {
	double da = a2 - a1;
	double aa = r * r * (da - sin(da)) / 2;
	point_t p1 = point_t(cos(a1), sin(a1)) * r + c;
	point_t p2 = point_t(cos(a2), sin(a2)) * r + c;
	return cross(p1, p2) / 2 + aa;
}

void circle_union() {
	for (int c = 1; c <= n; ++c) {
		int cvrcnt = 0;
		e.clear();
		for (int i = 1; i <= n; ++i) {
			if (i != c) {
				int rel = testCC(center[c], center[i], radius[c], radius[i]);
				if (rel == 2) ++cvrcnt;
				else if (rel == 0) {
					pair<double, double> paa = isCC(center[c], center[i], radius[c], radius[i]);
					add(paa.first, paa.second);	
				}
			}
		}
		if (e.size() == 0) {
			double a = pi * radius[c] * radius[c];
			cntarea[cvrcnt] -= a;
			cntarea[cvrcnt + 1] += a;
		} else {
			e.push_back(event_t(-pi, 1));
			e.push_back(event_t(pi, -2));
			sort(e.begin(), e.end());
			int esz = e.size();
			for (int i = 0; i < esz - 1; ++i) {
				cvrcnt += e[i].delta;
				double a = calc(center[c], radius[c], e[i].theta, e[i + 1].theta);
				cntarea[cvrcnt - 1] -= a;
				cntarea[cvrcnt] += a;
			}
		}
	}
}
