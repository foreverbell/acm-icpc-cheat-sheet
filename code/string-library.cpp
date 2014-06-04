// please note that all strings are indexed from 0
void kmp(const char *s, int *next) {
	--s, --next;
	next[1] = 0;
	int j = 0, n = strlen(s + 1);
	for (int i = 2; i <= n; ++i) {
		while (j > 0 && s[j + 1] != s[i]) j = next[j];
		if (s[j + 1] == s[i]) j = j + 1;
		next[i] = j;
	}
}

// s: text, t: text being searched, ex[i]: maximum l satisfying s[i...i+l-1] = t[0...l-1]
void exkmp(const char *s, const char *t, int *next, int *ex) {
	int n = strlen(t), m = strlen(s), k, c;
	next[0] = n;
	k = 0, c = 1;
	while (k + 1 < n && t[k] == t[k + 1]) ++k;
	next[1] = k;
	for (int i = 2; i < n; ++i) {
		int p = next[c] + c - 1;
		int l = next[i - c];
		if (i + l < p + 1) next[i] = l;
		else {
			k = max(0, p - i + 1);
			while (i + k < n && t[i + k] == t[k]) ++k;
			next[i] = k;
			c = i;
		}
	}
	k = c = 0;
	while (k < m && k < n && s[k] == t[k]) ++k;
	ex[0] = k;
	for (int i = 1; i < m; ++i) {
		int p = ex[c] + c - 1;
		int l = next[i - c];
		if (l + i < p + 1) ex[i] = next[i - c];
		else {
			k = max(0, p - i + 1);
			while (i + k < m && k < n && s[i + k] == t[k]) ++k;
			ex[i] = k;
			c = i;
		}
	}
}

// minimum representation of a string
int min_rep(string s) {
	s += s;
	int l = s.length(), i = 0, j = 1, k = 0;
	while (i + k < l && j + k < l) {
		if (s[i + k] == s[j + k]) {
			++k;
		} else {
			if (s[j + k] > s[i + k]) j += k + 1;
			else i += k + 1;
			k = 0;
			if (i == j) ++j;
		}
	}
	return min(i, j);
}

// l[i], the length of palindrome at the centre of i
int manacher(const char *s, int *l) {
	int n = strlen(s);
	for (int i = 0, j = 0, k; i < n * 2; i += k, j = max(j - k, 0)) {
		while (i >= j && i + j + 1 < n * 2 && s[(i - j) / 2] == s[(i + j + 1) / 2]) ++j;
		l[i] = j;
		for (k = 1; i >= k && j >= k && l[i - k] != j - k; ++k) {
			l[i + k] = min(l[i - k], j - k);
		}
	}
	return *max_element(l, l + n + n);
}