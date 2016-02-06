LL mult64(LL a, LL b, LL m) { // 64bit multiply 64bit
	a %= m, b %= m;
	LL ret = 0;
	for (; b; b >>= 1) {
		if (b & 1) ret = (ret + a) % m;
		a = (a + a) % m;
	}
	return ret;
}

LL fpow(LL a, LL p, int mod) { // fast power-modulo algorithm
	LL res = 1;
	for (; p; p >>= 1) {
		if (p & 1) res = (res * a) % mod; // using mult64 when mod is 64-bit
		a = (a * a) % mod;
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
	return (a % mod + mod) % mod; // C1: x & mod are co-prime
	return fpow(x, mod - 2, mod); // C2: mod is prime
}

void init_inverse(int mod) { // O(n), all multiplicative inverse, mod is prime
	inv[0] = inv[1] = 1;
	for (int i = 2; i < n; ++i) {
		inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod; // overflows?
	}
}

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

int sieve(int n, bool *isP, int *primes) { // generating primes using euler's sieve
	fill(isP + 2, isP + 1 + n, true); isP[1] = false;
	int pt = 0;
	for (int i = 2; i <= n; ++i) {
		if (isP[i]) primes[pt++] = i;
		for (int j = 0; j < pt && primes[j] * i <= n; ++j) {
			isP[primes[j] * i] = false;
			if (i % primes[j] == 0) break;
		}
	}
	return pt;
}

bool miller_rabin(LL n, LL b) { // miller-rabin prime test
	LL m = n - 1, cnt = 0;
	while (m % 2 == 0) m >>= 1, ++cnt;
	LL ret = fpow(b, m, n);
	if (ret == 1 || ret == n - 1) return true;
	--cnt;
	while (cnt >= 0) {
		ret = mult(ret, ret, n); // mult64
		if (ret == n - 1) return true;
		--cnt;
	}
	return false;
}

bool prime_test(LL n) {
	if (n < 2) return false;
	if (n < 4) return true;
	const int BASIC[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for (int i = 0; i < 12 && BASIC[i] < n; ++ i) {
		if (!miller_rabin(n, BASIC[i])) return false;
	}
	return true;
}

LL pollard_rho(LL n, LL seed) { // pollard-rho divisors factorization
	LL x, y;
	x = y = rand() % (n - 1) + 1;
	LL head = 1, tail = 2;
	while (true) {
		x = mult(x, x, n); // mult64
		x = (x + seed) % n;
		if (x == y) return n;
		LL d = gcd(max(x - y, y - x), n);
		if (1 < d && d < n) return d;
		if (++head == tail) y = x, tail <<= 1;
	}
}

void factorize(LL n, vector<LL> &divisor) {
	if (n == 1) return;
	if (prime_test(n)) divisor.push_back(n);
	else {
		LL d = n;
		while (d >= n) d = pollard_rho(n, rand() % (n - 1) + 1);
		factorize(n / d, divisor);
		factorize(d, divisor);
	}
}

// discrete-logarithm, finding y for equation k = x^y % mod
int discrete_logarithm(int x, int mod, int k) {
	if (mod == 1) return 0;
	int s = 1, g;
	for (int i = 0; i < 64; ++i) {
		if (s == k) return i;
		s = ((LL)s * x) % mod;
	}
	while ((g = gcd(x, mod)) != 1) {
		if (k % g) return -1;
		mod /= g;
	}
	static map<int, int> M; M.clear();
	int q = int(sqrt(double(euler(mod)))) + 1;
	for (int i = 0, b = 1; i < q; ++i) {
		if (M.find(b) == M.end()) M[b] = i;
		b = ((LL)b * x) % mod;
	}
	int p = fpow(x, q, mod);
	for (int i = 0, b = 1; i <= q; ++i) {
		int v = ((LL)k * inverse(b, mod)) % mod;
		if (M.find(v) != M.end()) {
			int y = i * q + M[v];
			if (y >= 64) return y;
		}
		b = ((LL)b * p) % mod;
	}
	return -1;
}

// primtive root, finding the number with order p-1 
int primtive_root(int p) {
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
