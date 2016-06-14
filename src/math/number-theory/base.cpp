LL mul64(LL a, LL b, LL m) { // 64-bit long long multiplication
  a %= m, b %= m;
  LL ret = 0;
  for (; b; b >>= 1) {
    if (b & 1) ret = (ret + a) % m;
    a = (a + a) % m;
  }
  return ret;
}

int fpow(int a, LL p, int mod) { // fast power-modulo 
  int res = 1;
  for (; p; p >>= 1) {
    // use mul64 if there is overflow
    if (p & 1) res = (1ll * res * a) % mod;
    a = (1ll * a * a) % mod;
  }
  return res;
}

int gcd(int x, int y) {
  return y == 0 ? x : gcd(y, x % y);
}

int exgcd(int x, int y, int &a, int &b) { // extended gcd, ax + by = g
  int a0 = 1, a1 = 0, b0 = 0, b1 = 1;
  while (y != 0) {
    a0 -= x / y * a1; swap(a0, a1);
    b0 -= x / y * b1; swap(b0, b1);
    x %= y; swap(x, y);
  }
  if (x < 0) a0 = -a0, b0 = -b0, x = -x;
  a = a0, b = b0;
  return x;
}
