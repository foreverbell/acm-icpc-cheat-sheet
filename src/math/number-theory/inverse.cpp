int inverse(int x, int mod) { // multiplicative inverse
  int a = 0, b = 0;
  if (exgcd(x, mod, a, b) != 1) return -1;
  return (a % mod + mod) % mod; // case 1: x & mod are co-prime
  return fpow(x, mod - 2, mod); // case 2: mod is prime
}

void inverse_all(int mod) { // O(n), mod is prime
  inv[0] = inv[1] = 1;
  for (int i = 2; i < n; ++i) {
    inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod; // overflows?
  }
}
