void set_circle(point_t &p, double &r, point_t a, point_t b) {
	r = dist(a, b) / 2;
	p = (a + b) / 2;
}

void set_circle(point_t &p, double &r, point_t a, point_t b, point_t c) {
	if (dblcmp(cross(b - a, c - a)) == 0) {
		if (dist(a, c) > dist(b, c)) {
			r = dist(a, c) / 2;
			p = (a + c) / 2;
		} else {
			r = dist(b, c) / 2;
			p = (b + c) / 2;
		}
	} else {
		p = circumcenter(a, b, c);
		r = dist(p, a);
	}
}

bool in_circle(point_t &p, double &r, point_t x) {
	return dblcmp(dist(x, p) - r) <= 0;
}

pair<point_t, double> minimum_circle(int n, point_t *p) {
	point_t c = point_t(0, 0);
	double r = 0;
	random_shuffle(p + 1, p + 1 + n);
	set_circle(c, r, p[1], p[2]);
	for (int i = 3; i <= n; ++i) {
		if (in_circle(c, r, p[i])) continue;
		set_circle(c, r, p[i], p[1]);
		for (int j = 2; j < i; ++j) {
			if (in_circle(c, r, p[j])) continue;
			set_circle(c, r, p[i], p[j]);
			for (int k = 1; k < j; ++k) {
				if (in_circle(c, r, p[k])) continue;
				set_circle(c, r, p[i], p[j], p[k]);
			}
		}
	}
	return make_pair(c, r);
}
