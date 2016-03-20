double dot(point3_t p1, point3_t p2) {
  return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

point3_t cross(point3_t p1, point3_t p2) {
  return point3_t(p1.y * p2.z - p1.z * p2.y, p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x);
}

double volume(point3_t p1, point3_t p2, point3_t p3, point3_t p4) {
  point3_t v1 = cross(p2 - p1, p3 - p1);
  p4 = p4 - p1;
  return dot(v1, p4) / 6;
}

double area(point3_t p1, point3_t p2, point3_t p3) {
  return cross(p2 - p1, p3 - p1).length() / 2;
}

pair<point3_t, point3_t> isFF(point3_t p1, point3_t o1, point3_t p2, point3_t o2) {
  point3_t e = cross(o1, o2), v = cross(o1, e);
  double d = dot(o2, v);
  if (fabs(d) < eps) throw - 1;
  point3_t q = p1 + (v * (dot(o2, p2 - p1) / d));
  return make_pair(q, q + e);
}

double distLL(point3_t p1, point3_t u, point3_t p2, point3_t v) {
  double s = dot(u, v) * dot(v, p1 - p2) - dot(v, v) * dot(u, p1 - p2);
  double t = dot(u, u) * dot(v, p1 - p2) - dot(u, v) * dot(u, p1 - p2);
  double deno = dot(u, u) * dot(v, v) - dot(u, v) * dot(u, v);
  if (dblcmp(deno) == 0) return dist(p1, p2 + v * (dot(p1 - p2, u) / dot(u, v)));
  s /= deno; t /= deno;
  point3_t a = p1 + u * s, b = p2 + v * t;
  return dist(a, b);
}