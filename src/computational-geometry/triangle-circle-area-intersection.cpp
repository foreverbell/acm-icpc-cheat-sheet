double areaTC(point_t ct, double r, point_t p1, point_t p2) { // intersected area
  double a, b, c, x, y, s = cross(p1 - ct, p2 - ct) / 2;
  a = dist(ct, p2), b = dist(ct, p1), c = dist(p1, p2);
  double hr2 = r * r / 2, cr2 = c * c * r * r;
  if (a <= r && b <= r) {
    return s;
  } else if (a < r && b >= r) {
    x = (dot(p1 - p2, ct - p2) + sqrt(cr2 - sqr(cross(p1 - p2, ct - p2)))) / c;
    return asin(s * (c - x) * 2 / c / b / r) * hr2 + s * x / c;
  } else if (a >= r && b < r) {
    y = (dot(p2 - p1, ct - p1) + sqrt(cr2 - sqr(cross(p2 - p1, ct - p1)))) / c;
    return asin(s * (c - y) * 2 / c / a / r) * hr2 + s * y / c;
  } else {
    if (fabs(2 * s) >= r * c || dot(p2 - p1, ct - p1) <= 0 || dot(p1 - p2, ct - p2) <= 0) {
      if (dot(p1 - ct, p2 - ct) < 0) {
        if (cross(p1 - ct, p2 - ct) < 0) {
          return (-pi - asin(s * 2 / a / b)) * hr2;
        } else {
          return (pi - asin(s * 2 / a / b)) * hr2;
        }
      } else {
        return asin(s * 2 / a / b) * hr2;
      }
    } else {
      x = (dot(p1 - p2, ct - p2) + sqrt(cr2 - sqr(cross(p1 - p2, ct - p2)))) / c;
      y = (dot(p2 - p1, ct - p1) + sqrt(cr2 - sqr(cross(p2 - p1, ct - p1)))) / c;
      return (asin(s * (1 - x / c) * 2 / r / b) + asin(s * (1 - y / c) * 2 / r / a)) * hr2 + s * ((y + x) / c - 1);
    }
  }
}

double areaTC(point_t ct, double r, point_t p1, point_t p2, point_t p3) {
  return areaTC(ct, r, p1, p2) + areaTC(ct, r, p2, p3) + areaTC(ct, r, p3, p1);
}