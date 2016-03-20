// l[i] is the length of palindrome at the centre of i
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