template<typename T, int N> 
struct matrix_t {
  T x[N + 1][N + 1];
  matrix_t(T v) {
    memset(x, 0, sizeof(x));
    for (int i = 1; i <= N; ++i) x[i][i] = v;
  }
  matrix_t operator*(const matrix_t &r) {
    matrix_t p = 0;
    for (int k = 1; k <= N; ++k) {
      for (int i = 1; i <= N; ++i) {
        if (x[i][k] == 0) continue;
        for (int j = 1; j <= N; ++j) {
          p.x[i][j] += x[i][k] * r.x[k][j];
          // p.x[i][j] %= mod;
        }
      }
    }
    return p;
  }
  matrix_t power(LL p) {
    matrix_t r = 1, a = *this;
    for (; p; p >>= 1) {
      if (p & 1) r = r * a;
      a = a * a;
    }
    return r;
  }
  T determinant() const {
    T r = 1, det[N + 1][N + 1];
    for (int i = 1; i <= N; ++i) memcpy(det[i], x[i], sizeof(x[i])); 
    for (int i = 1; i <= N; ++i) {
      for (int j = i + 1; j <= N; ++j) {
        while (det[j][i] != 0) {
          T ratio = det[i][i] / det[j][i];
          for (int k = i; k <= N; ++k) {
            det[i][k] -= ratio * det[j][k];
            swap(det[i][k], det[j][k]);
          }
          r = -r;
        }
      }
      r = r * det[i][i];
    }
    return r;
  }
};

/* For 3x3 symmetric matrix only, eigen vectors are returned by columns. */
typedef matrix_t<double, 3> mat3_t;
mat3_t eigen(const mat3_t &mat, double &lambda1, double &lambda2, double &lambda3) {
  double m[4][4];
  mat3_t r = 1;
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) m[i][j] = mat.x[i][j];
  }
  for (int times = 0; times < 32; ++times) {
    if (dblcmp(m[1][2]) == 0 && dblcmp(m[1][3]) == 0 && dblcmp(m[2][3]) == 0) break;
#define ELIMINATE(i, j, k) \
    if (m[i][j] != 0) { \
      double u = (m[j][j] - m[i][i]) / 2 / m[i][j]; \
      double u2 = u * u; \
      double u2p1 = u2 + 1; \
      double t = (u2p1 != u2) ? ((u < 0) ? -1 : 1) * (sqrt(u2p1) - fabs(u)) : 0.5 / u; \
      double c = 1.0 / sqrt(t * t + 1); \
      double s = c * t; \
      m[i][i] -= t * m[i][j], m[j][j] += t * m[i][j]; \
      m[i][j] = m[j][i] = 0; \
      double temp = c * m[i][k] - s * m[j][k]; \
      m[j][k] = m[k][j] = s * m[i][k] + c * m[j][k]; \
      m[i][k] = m[k][i] = temp; \
      for (int a = 1; a <= 3; ++a) { \
        double temp = c * r.x[a][i] - s * r.x[a][j]; \
        r.x[a][j] = s * r.x[a][i] + c * r.x[a][j]; \
        r.x[a][i] = temp; \
      } \
    }
    ELIMINATE(1, 2, 3);
    ELIMINATE(1, 3, 2);
    ELIMINATE(2, 3, 1);
#undef ELIMINATE
  }
  lambda1 = m[1][1], lambda2 = m[2][2], lambda3 = m[3][3];
  return r;
}