struct quater_t {
  double w, x, y, z; // w + xi + yj + zk
  quater_t(double tw, const point3_t &v) : w(tw), x(v.x), y(v.y), z(v.z) { }
  quater_t(double tw, double tx, double ty, double tz) : w(tw), x(tx), y(ty), z(tz) { }
  double length() const {
    return sqrt(w * w + x * x + y * y + z * z);
  }
  point3_t vector() const {
    return point3_t(x, y, z);
  }
  quater_t conjugate() const {
    return quater_t(w, -x, -y, -z);
  }
  quater_t operator*(const quater_t &q2) {
    return quater_t(w * q2.w - x * q2.x - y * q2.y - z * q2.z, w * q2.x + x * q2.w + y * q2.z - z * q2.y, w * q2.y - x * q2.z + y * q2.w + z * q2.x, w * q2.z + x * q2.y - y * q2.x + z * q2.w);
  }
};

void rotate(point3_t axis, point3_t p, double angle) {
  quater_t q = quater_t(cos(angle / 2), axis * sin(angle / 2));
  return (q * quater_t(0, p) * q.conjugate()).vector();
}