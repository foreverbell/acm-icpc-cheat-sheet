const int B = 10000, D = 4;
struct bnum_t {
	int l;
	vector<int> b;
	bnum_t(int n) {
		b.push_back(0);
		if (n == 0) l = 1, b.push_back(0);
		else {
			l = 0;
			for (int i = 1; n; ++i, n /= B) ++l, b.push_back(n % B);
		}
	}
	bnum_t() { *this = bnum_t(0); }
	bnum_t(char *str) {
		l = 0, b.push_back(0);
		int temp = strlen(str);
		for (int i = temp - 1; i >= 0; i -= D) {
			int v = 0;
			for (int j = 0, p10 = 1; j < D && i - j >= 0; ++j, p10 *= 10) v += (str[i - j] - '0') * p10;
			++l, b.push_back(v);
		}
	}
	friend ostream &operator<<(ostream &os, const bnum_t &r) {
		os << r.b[r.l];
		for (int i = r.l - 1; i >= 1; --i) os << setfill('0') << setw(D) << r.b[i];
		return os;
	}
	bnum_t operator+(const bnum_t &r) {
		bnum_t f(*this);
		f.l = max(l, r.l);
		f.b.resize(f.l + 5);
		for (int i = 1; i <= min(f.l, r.l); ++i) {
			f.b[i] += r.b[i];
			if (f.b[i] / B) f.b[i + 1] += f.b[i] / B, f.b[i] %= B;
		}
		while (f.b[f.l + 1]) f.l += 1;
		f.b.resize(f.l + 1);
		return f;
	}
	bnum_t operator-(const bnum_t &r) { // assume a > b
		bnum_t f = *this;
		f.l = max(l, r.l);
		for (int i = 1; i <= min(f.l, r.l); ++i) {
			f.b[i] -= r.b[i];
			while (f.b[i] < 0) f.b[i] += B, --f.b[i + 1];
		}
		while (f.b[f.l] == 0) f.l -= 1;
		f.b.resize(f.l + 1);
		return f;
	}
	bnum_t operator*(const bnum_t &r) {
		bnum_t f = 0;
		f.l = l + r.l - 1;
		f.b.resize(f.l + 5);
		for (int i = 1; i <= l; ++i) {
			for (int j = 1; j <= r.l; ++j) {
				f.b[i + j - 1] += b[i] * r.b[j];
				if (f.b[i + j - 1] / B) f.b[i + j] += f.b[i + j - 1] / B, f.b[i + j - 1] %= B;
			}
		}
		while (f.b[f.l + 1]) f.l += 1;
		f.b.resize(f.l + 1);
		return f;
	}
	bnum_t operator*(const int &r) {
		return (*this) * bnum_t(r);
	}
	bnum_t operator/(const int &r) { // assume a > b
		bnum_t f = *this;
	 	for (int i = f.l; i >= 1; --i) f.b[i - 1] += (f.b[i] % r) * B, f.b[i] /= r;
		while (f.b[f.l] == 0) f.l -= 1;
		f.b.resize(f.l + 1);
		return f;
	}
};