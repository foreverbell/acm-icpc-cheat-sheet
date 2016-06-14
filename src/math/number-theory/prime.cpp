bool isp[maxN];
int primes[maxN], pt;

int sieve(int n) { // generating primes using euler's sieve
  fill(isp + 2, isp + 1 + n, true);
  isp[1] = false;
  pt = 0;
  for (int i = 2; i <= n; ++i) {
    if (isp[i]) primes[pt++] = i;
    for (int j = 0; j < pt && primes[j] * i <= n; ++j) {
      isp[primes[j] * i] = false;
      if (i % primes[j] == 0) break;
    }
  }
  return pt;
}

bool miller_rabin(LL n, LL b) {
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
