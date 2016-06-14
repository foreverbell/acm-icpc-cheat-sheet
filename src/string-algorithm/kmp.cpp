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

// s: text, t: pattern, ex[i]: maximum l satisfying s[i...i+l-1] = t[0...l-1]
void exkmp(const char *s, const char *t, int *next, int *ex) {
  int n = strlen(t), m = strlen(s), k, c;
  next[0] = n;
  k = 0, c = 1;
  while (k + 1 < n && t[k] == t[k + 1]) ++k;
  next[1] = k;
  for (int i = 2; i < n; ++i) {
    int p = next[c] + c - 1, l = next[i - c];
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
    int p = ex[c] + c - 1, l = next[i - c];
    if (l + i < p + 1) ex[i] = next[i - c];
    else {
      k = max(0, p - i + 1);
      while (i + k < m && k < n && s[i + k] == t[k]) ++k;
      ex[i] = k;
      c = i;
    }
  }
}