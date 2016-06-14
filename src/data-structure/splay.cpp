struct node_t {
  node_t();
  void update();
  int dir() {
    return (this == p->ch[1]);
  }
  void setc(node_t *c, int d) {
    ch[d] = c, c->p = this;
  }
  node_t *p, *ch[2];
  int size, cnt; // maintain tag from top to bottom (via find).
} s[maxN], *nil = s, *root;

node_t::node_t() {
  p = ch[0] = ch[1] = nil;
}

void node_t::update() {
  if (this == nil) return;
  size = ch[0]->size + ch[1]->size + cnt;
}

node_t *newNode(int cnt) {
  ++pt;
  s[pt].cnt = cnt; s[pt].p = s[pt].ch[0] = s[pt].ch[1] = nil;
  s[pt].update();
  return s + pt;
}

void rotate(node_t *t) {
  node_t *p = t->p;
  p->p->update();
  p->update();
  t->update();
  int d = t->dir();
  p->p->setc(t, p->dir());
  p->setc(t->ch[!d], d);
  t->setc(p, !d);
  if (p == root) root = t;
  p->update(), t->update();
}

node_t *splay(node_t *t, node_t *dst = nil) {
  while (t->p != dst) {
    if (t->p->p == dst) rotate(t);
    else if (t->dir() == t->p->dir()) rotate(t->p), rotate(t);
    else rotate(t), rotate(t);
  }
  t->update();
  return t;
}

node_t *prev(node_t *p) {
  splay(p);
  p = p->ch[0], p->update();
  while (p->ch[1] != nil) p = p->ch[1], p->update();
  return p;
}

node_t *succ(node_t *p) {
  splay(p);
  p = p->ch[1], p->update();
  while (p->ch[0] != nil) p = p->ch[0], p->update();
  return p;
}

void insert(node_t *y, node_t *x) { // insert node x after y
  splay(y);
  if (y->ch[1] == nil) {
    y->ch[1] = x;
    x->p = y;
    y->update();
  } else {
    y = y->ch[1], y->update();
    while (y->ch[0] != nil) y = y->ch[0], y->update();
    y->ch[0] = x;
    x->p = y;
    y->update();
  }
  splay(x);
}

void removeAll(node_t *x) { // remove all the whole subtree of x
  x->p->update();
  x->p->ch[x->dir()] = nil;
  x->p->update();
  splay(x->p);
  x->p = nil;
}

void remove(node_t *x) { // remove the single node x
  node_t *p = prev(x); node_t *s = succ(x);
  splay(p);
  splay(s, p);
  removeAll(s->ch[0]);
}

node_t *find(node_t *t, int k) {
  t->update();
  if (t->ch[0]->size < k && t->ch[0]->size + t->cnt >= k) return t;
  if (t->ch[0]->size >= k) return find(t->ch[0], k);
  return find(t->ch[1], k - t->ch[0]->size - t->cnt);
}

node_t *findAndSplit(node_t *t, int k) {
  t->update();
  if (t->ch[0]->size < k && t->ch[0]->size + t->cnt >= k) {
    int cnt = t->cnt;
    k -= t->ch[0]->size;
    t->cnt = 1;
    splay(t);
    node_t *p = prev(t);
    if (k - 1) insert(p, newNode(k - 1));
    if (cnt - k) insert(t, newNode(cnt - k));
    return t;
  }
  if (t->ch[0]->size >= k) return findAndSplit(t->ch[0], k);
  return findAndSplit(t->ch[1], k - t->ch[0]->size - t->cnt);
}

void init() {
  pt = 0, nil->p = nil->ch[0] = nil->ch[1] = nil;
}

node_t *expose(node_t *x, node_t *y) {
  x = prev(x), y = succ(y);
  return splay(y, splay(x))->ch[0];
}
