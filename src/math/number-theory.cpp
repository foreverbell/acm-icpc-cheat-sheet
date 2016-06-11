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

int inverse(int x, int mod) { // multiplicative inverse
  int a = 0, b = 0;
  if (exgcd(x, mod, a, b) != 1) return -1;
  return (a % mod + mod) % mod; // case 1: x & mod are co-prime
  return fpow(x, mod - 2, mod); // case 2: mod is prime
}

void invall(int mod) { // O(n), mod is prime
  inv[0] = inv[1] = 1;
  for (int i = 2; i < n; ++i) {
    inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod; // overflows?
  }
}

// https://math.stackexchange.com/questions/120070/chinese-remainder-theorem-with-non-pairwise-coprime-moduli
LL crt(int k, int *p, int *b) { // chinese remainder theorem
  LL N = 1, ans = 0;
  for (int i = 0; i < k; ++i) N *= p[i];
  for (int i = 0; i < k; ++i) {
    LL mult = (inverse(N / p[i], p[i]) * (N / p[i])) % N;
    mult = (mult * b[i]) % N;
    ans += mult; ans %= N;
  }
  if (ans < 0) ans += N;
  return ans;
}

int sieve(int n) { // generating primes using euler's sieve
  fill(isp + 2, isp + 1 + n, true);
  isp[1] = false;
  int pt = 0;
  for (int i = 2; i <= n; ++i) {
    if (isp[i]) primes[pt++] = i;
    for (int j = 0; j < pt && primes[j] * i <= n; ++j) {
      isp[primes[j] * i] = false;
      if (i % primes[j] == 0) break;
    }
  }
  return pt;
}

bool miller_rabin(LL n, LL b) { // always call ptest
  LL m = n - 1, cnt = 0;
  while (m % 2 == 0) m >>= 1, ++cnt;
  LL ret = fpow(b, m, n);
  if (ret == 1 || ret == n - 1) return true;
  while (cnt > 0) {
    ret = mul64(ret, ret, n);
    if (ret == n - 1) return true;
    --cnt;
  }
  return false;
}

bool ptest(LL n) { // miller-rabin primality test
  if (n < 2) return false;
  if (n < 4) return true;
  const int BASIC[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
  for (int i = 0; i < 12 && BASIC[i] < n; ++i) {
    if (!miller_rabin(n, BASIC[i])) return false;
  }
  return true;
}

LL pollard_rho(LL n, LL seed) { // always call factorize
  LL x, y;
  x = y = rand() % (n - 1) + 1;
  int head = 1, tail = 2;
  while (true) {
    x = mul64(x, x, n);
    x = (x + seed) % n;
    if (x == y) return n;
    LL d = gcd(max(x - y, y - x), n);
    if (1 < d && d < n) return d;
    if (++head == tail) y = x, tail <<= 1;
  }
}

void factorize(LL n, vector<LL> &divisor) { // pollard-rho factorization
  if (n == 1) return;
  if (ptest(n)) divisor.push_back(n);
  else {
    LL d = n;
    while (d >= n) d = pollard_rho(n, rand() % (n - 1) + 1);
    factorize(n / d, divisor);
    factorize(d, divisor);
  }
}

vector<LL> divisors(vector<LL> d) {
  vector<LL> ret = {1};
  sort(d.begin(), d.end());
  for (int i = 0, count = 1; i < d.size(); ++i) {
    if (i + 1 == d.size() || d[i] != d[i + 1]) {
      int c = ret.size();
      ret.resize(ret.size() * (count+1));
      LL n = 1;
      for (int j = 1; j <= count + 1; ++j) {
        for (int k = 0; k < c; ++k) {
          ret[(j-1)*c+k] = ret[k]*n;
        }
        n *= d[i];
      }
      count = 1;
    } else count += 1;
  }
  sort(ret.begin(), ret.end());
  return ret;
}

LL count_prime(LL n) { // counting primes with dp method
  int root = sqrt(double(n));
  int pt = sieve(root + 1);
  vector<LL> v;
  for (int i = 1; i <= root + 1; ++i) v.push_back(n / i);
  int last = v.back();
  for (int i = last - 1; i >= 0; --i) v.push_back(i);
  vector<LL> dp(v.size()); // dp(v,p)=dp(v,p-1)-(dp(v/p,p-1)-dp(p-1,p-1))
  for (int i = 0; i < v.size() - 1; ++i) {
    dp[i] = v[i] - 1;
  }
  for (int i = 0; i < pt; ++i) {
    int p = primes[i];
    LL p2 = 1ll * p * p;
    for (int j = 0; j < v.size(); ++j) {
      LL k = v[j];
      if (k < p2) break;
      k /= p;
      dp[j] -= dp[(k <= last ? root + 1 + last - k : n / k) - 1] - i; // <=?
    }
  }
  return dp[0];
}

// discrete-logarithm, finding y for equation k = x^y % mod
int discrete_logarithm(int x, int mod, int k) {
  if (mod == 1) return 0;
  int s = 1, g;
  for (int i = 0; i < 64; ++i) {
    if (s == k) return i;
    s = (1ll * s * x) % mod;
  }
  while ((g = gcd(x, mod)) != 1) {
    if (k % g) return -1;
    mod /= g;
  }
  static unordered_map<int, int> M; M.clear();
  int q = int(sqrt(double(euler(mod)))) + 1;
  for (int i = 0, b = 1; i < q; ++i) {
    if (M.find(b) == M.end()) M[b] = i;
    b = (1ll * b * x) % mod;
  }
  int p = fpow(x, q, mod);
  for (int i = 0, b = 1; i <= q; ++i) {
    int v = (1ll * k * inverse(b, mod)) % mod;
    if (M.find(v) != M.end()) {
      int y = i * q + M[v];
      if (y >= 64) return y;
    }
    b = (1ll * b * p) % mod;
  }
  return -1;
}

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
