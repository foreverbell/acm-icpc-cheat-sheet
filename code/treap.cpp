struct node {
	int v, key, size;
	node *c[2];
	void resize() { size = c[0]->size + c[1]->size + 1; }
};
node *newNode(int _v, node *n) {
	++ref;
	pool[ref].v = _v, pool[ref].c[0] = pool[ref].c[1] = n, pool[ref].size = 1, pool[ref].key = rand();
	return &pool[ref];
}
struct Treap {
	node *root, *nil;
	void rotate(node *&t, int d) {
		node *c = t->c[d];
		t->c[d] = c->c[!d];
		c->c[!d] = t;
		t->resize(); c->resize();
		t = c;
	}
	void insert(node *&t, int x) {
		if (t == nil) t = newNode(x, nil);
		else {
			if (x == t->v) return;
			int d = x > t->v;
			insert(t->c[d], x);
			if (t->c[d]->key < t->key) rotate(t, d);
			else t->resize();
		}
	}
	void remove(node *&t, int x) {
		if (t == nil) return;
		if (t->v == x) {
			int d = t->c[1]->key < t->c[0]->key;
			if (t->c[d] == nil) {
				t = nil;
				return;
			}
			rotate(t, d);
			remove(t->c[!d], x);
		} else {
			int d = x > t->v;
			remove(t->c[d], x);
		}
		t->resize();
	}
	int rank(node *t, int x) {
		if (t == nil) return 0;
		int r = t->c[0]->size;
		if (x == t->v) return r + 1;
		if (x < t->v) return rank(t->c[0], x);
		return r + 1 + rank(t->c[1], x);
	}
	int select(node *t, int k) {
		int r = t->c[0]->size;
		if (k == r + 1) return t->v;
		if (k <= r) return select(t->c[0], k);
		return select(t->c[1], k - r - 1);
	}
	int size() {
		return root->size;
	}
	void init(int *a, int n) {
		nil = newNode(0, 0);
		nil->size = 0, nil->key = ~0U >> 1;
		root = nil;
	}
};