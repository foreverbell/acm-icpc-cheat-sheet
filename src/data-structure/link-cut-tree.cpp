struct node_t {
  node_t();
  node_t *ch[2], *p;
  int size, root;
  int dir() { return this == p->ch[1]; }
  void setc(node_t *c, int d) { ch[d] = c, c->p = this; }
  void update() { size = ch[0]->size + ch[1]->size + 1; }
} s[maxn], *nil = s;

node_t::node_t() {
  size = 1, root = true;
  ch[0] = ch[1] = p = nil;
}

void rotate(node_t *t) {
  node_t *p = t->p;
  int d = t->dir();
  if (!p->root) {
    p->p->setc(t, p->dir());
  } else {
    p->root = false, t->root = true;
    t->p = p->p; // Path Parent
  }
  p->setc(t->ch[!d], d);
  t->setc(p, !d);
  p->update(), t->update();
}

void splay(node_t *t) {
  // t->update(); // tag!
  while (!t->root) {
    // if (!t->p->root) t->p->p->update(); t->p->update(), t->update(); // !
    if (!t->p->root) rotate(t->dir() == t->p->dir() ? t->p : t);
    rotate(t);
  }
}

void access(node_t *x) { // Ask u, v: access(u), access(v, true), x = LCA
  node_t *y = nil;
  while (x != nil) {
    splay(x);
    // if (x->p == nil) at second call, x->ch[1](rev) + (x)_single + y
    x->ch[1]->root = true;
    x->ch[1] = y, y->root = false;
    x->update();
    y = x, x = x->p;
  }
}

void cut(node_t *x) {
  access(x);
  splay(x);
  x->ch[0]->root = true;
  x->ch[0]->p = nil;
  x->ch[0] = nil;
}

void link(node_t *x, node_t *y) {
  access(y);
  splay(y);
  y->p = x;
  access(y);
}

void init() {
  nil->size = 0;
}
