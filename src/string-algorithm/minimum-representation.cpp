int minimum_representation(string s) {
  s += s;
  int l = s.length(), i = 0, j = 1, k = 0;
  while (i + k < l && j + k < l) {
    if (s[i + k] == s[j + k]) ++k;
    else {
      if (s[j + k] > s[i + k]) j += k + 1;
      else i += k + 1;
      k = 0;
      if (i == j) ++j;
    }
  }
  return min(i, j);
}
