vector<point_t> tanCP(point_t c, double r, point_t p) {
	double x = dot(p - c, p - c);
	double d = x - r * r;
	vector<point_t> res;
	if (d < -eps) return res;
	if (d < 0) d = 0;
	point_t q1 = (p - c) * (r * r / x);
	point_t q2 = ((p - c) * (-r * sqrt(d) / x)).rot90(); // rot90: (-y, x)
	res.push_back(c + q1 - q2);
	res.push_back(c + q1 + q2);
	return res;
}

vector<seg_t> tanCC(point_t c1, double r1, point_t c2, double r2) {
	vector<seg_t> res;
	if (abs(r1 - r2) < eps) {
		point_t dir = c2 - c1;
		dir = (dir * (r1 / dir.l())).rot90();
		res.push_back(seg_t(c1 + dir, c2 + dir));
		res.push_back(seg_t(c1 - dir, c2 - dir));
	} else {
		point_t p = ((c1 * -r2) + (c2 * r1)) / (r1 - r2);
		vector<point_t> ps = tanCP(c1, r1, p), qs = tanCP(c2, r2, p);
		for (int i = 0; i < ps.size() && i < qs.size(); ++i) {
			res.push_back(seg_t(ps[i], qs[i]));
		}
	}
	point_t p = ((c1 * r2) + (c2 * r1)) / (r1 + r2);
	vector<point_t> ps = tanCP(c1, r1, p), qs = tanCP(c2, r2, p);
	// point_t tmp = (c2 - c1).rot90().rot90().rot90();
	for (int i = 0; i < ps.size() && i < qs.size(); ++i) {
		/* if (dblcmp(dist(ps[i], qs[i])) == 0) {
			qs[i] = qs[i] + tmp;
			tmp = tmp.rot90().rot90();
		}*/ 
		res.push_back(seg_t(ps[i], qs[i]));
	}
	return res;
}