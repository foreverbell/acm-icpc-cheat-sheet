// Assume d <= r1 + r2 && d >= |r1 - r2|
pair<point_t, point_t> isCC(point_t c1, point_t c2, double r1, double r2) {
  if (r1 < r2) swap(c1, c2), swap(r1, r2);
  double d = dist(c1, c2);
  double x1 = c1.x, x2 = c2.x, y1 = c1.y, y2 = c2.y;
  double mid = atan2(y2 - y1, x2 - x1);
  double a = r1, c = r2;
  double t = acos(max(0.0, a * a + d * d - c * c) / (2 * a * d));
  point_t p1 = point_t(cos(mid - t) * r1, sin(mid - t) * r1) + c1;
  point_t p2 = point_t(cos(mid + t) * r1, sin(mid + t) * r1) + c1;
  return make_pair(p1, p2);
}

int testCC(point_t c1, point_t c2, double r1, double r2) {
  double d = dist(c1, c2);
  if (dblcmp(r1 + r2 - d) <= 0) return 1; // not intersected or tged
  if (dblcmp(r1 + d - r2) <= 0) return 2; // C1 inside C2
  if (dblcmp(r2 + d - r1) <= 0) return 3; // C2 inside C1
  return 0; // intersected
}

point_t isCL(point_t a, point_t b, point_t o, double r) {
  double x0 = o.x, y0 = o.y;
  double x1 = a.x, y1 = a.y;
  double x2 = b.x, y2 = b.y;
  double dx = x2 - x1, dy = y2 - y1;
  double A = dx * dx + dy * dy;
  double B = 2 * dx * (x1 - x0) + 2 * dy * (y1 - y0);
  double C = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0) - r * r;
  double delta = B * B - 4 * A * C;
  if (delta >= 0) {
    delta = sqrt(delta);
    double t1 = (-B - delta) / 2 / A;
    double t2 = (-B + delta) / 2 / A;
    if (dblcmp(t1) >= 0) return point_t(x1 + t1 * dx, y1 + t1 * dy); // Ray
    if (dblcmp(t2) >= 0) return point_t(x1 + t2 * dx, y1 + t2 * dy);
  }
  return point_t();
}