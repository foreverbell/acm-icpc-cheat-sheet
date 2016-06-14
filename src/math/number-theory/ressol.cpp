// primitive root, finding the number with order p-1 
int primitive_root(int p) {
  vector<int> factor;
  int tmp = p - 1;
  for (int i = 2; i * i <= tmp; ++i) {
    if (tmp % i == 0) {
      factor.push_back(i);
      while (tmp % i == 0) tmp /= i;
    }
  }
  if (tmp != 1) factor.push_back(tmp);
  for (int root = 1; ; ++root) {
    bool flag = true;
    for (int i = 0; i < factor.size(); ++i) {
      if (fpow(root, (p - 1) / factor[i], p) == 1) {
        flag = false;
        break;
      }
    }
    if (flag) return root;
  }
}

int legendre(int n, int p) {
  return fpow(n, (p - 1) / 2, p);
}

// a.k.a Tonelli–Shanks algorithm
int ressol(int n, int p) {
  n %= p;
  if (n == 0) return 0;
  if (legendre(n, p) != 1) return -1;
  int q = p - 1, s = 0, z, c;
  while (q % 2 == 0) q /= 2, ++s;
  while (true) {
    z = rand() % (p - 1) + 1;
    if (legendre(z, p) == p - 1) break; 
  }
  c = fpow(z, q, p);
  int r = fpow(n, (q + 1) / 2, p), t = fpow(n, q, p), m = s;
  while (true) {
    if (t == 1) return r;
    for (int i = 0, tmp = t; i < m; ++i, tmp = 1ll * tmp * tmp % p) {
      if (tmp == 1) {
        int b = fpow(c, 1 << (m - i - 1), p);
        c = 1ll * b * b % p;
        r = 1ll * r * b % p;
        t = 1ll * t * c % p;
        m = i;
        break;
      }
    }
  }
  return r;
}
