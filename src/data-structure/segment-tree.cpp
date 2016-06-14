int get_id(int l, int r) {
  return l + r | l != r;
}

// implement push_down & update
void insert(int l, int r, int a, int b) {
  int id = get_id(l, r);
  if (a <= l && r <= b) {
    // do modification here
  } else if (l <= b && a <= r) {
    push_down(l, r);
    int m = l + r >> 1;
    insert(l, m, a, b);
    insert(m + 1, r, a, b);
    update(l, r);
  }
}