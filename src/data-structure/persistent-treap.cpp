struct node_t {
  int key, cnt, size;
  string v;
  node_t *c[2];
  void resize() {
    size = (c[0] ? c[0]->size : 0) + cnt + (c[1] ? c[1]->size : 0);
  }
} *nil;

node_t *newNode(string v, node_t *l = nil, node_t *r = nil, int key = rand()) {
  node_t *ret = new node_t();
  ret->key = key;
  ret->cnt = v.length(), ret->v = v;
  ret->c[0] = l, ret->c[1] = r;
  ret->resize();
  return ret;
}

void init() {
  nil = newNode("", 0, 0);
  nil->size = 0, nil->key = ~0U >> 1;
}

struct PersistentTreap {
  node_t *root;

  node_t *splitL(node_t *a, int size) {
    if (a == nil || size == 0) return nil;
    if (a->c[0]->size >= size) return splitL(a->c[0], size);
    if (a->c[0]->size + a->cnt >= size) return newNode(a->v.substr(0, size - a->c[0]->size), a->c[0], nil, a->key);
    return newNode(a->v, a->c[0], splitL(a->c[1], size - a->c[0]->size - a->cnt), a->key);
  }

  node_t *splitR(node_t *a, int size) {
    if (a == nil || size == 0) return nil;
    if (a->c[1]->size >= size) return splitR(a->c[1], size);
    if (a->c[1]->size + a->cnt >= size) return newNode(a->v.substr(a->v.length() - (size - a->c[1]->size), size - a->c[1]->size), nil, a->c[1], a->key);
    return newNode(a->v, splitR(a->c[0], size - a->c[1]->size - a->cnt), a->c[1], a->key);
  }

  node_t *merge(node_t *a, node_t *b) {
    if (a == nil) return b;
    if (b == nil) return a;
    if (a->key > b->key) return newNode(a->v, a->c[0], merge(a->c[1], b), a->key);
    return newNode(b->v, merge(a, b->c[0]), b->c[1], b->key);
  }

  node_t *insert(string v, int p) { // insert after p
    int l = root->size;
    return merge(merge(splitL(root, p), newNode(v, nil, nil)), splitR(root, l - p));
  }

  node_t *remove(int x, int y) { // remove [x, y]
    int l = root->size;
    return merge(splitL(root, x - 1), splitR(root, l - y));
  }
};
