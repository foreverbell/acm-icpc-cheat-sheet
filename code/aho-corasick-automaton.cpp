struct trie_t {
	bool flag;
	trie_t *child[C], *fail;
} trie[maxn], *root;
trie_t *new_trie() { return &trie[++pt]; }

void add(char *str) {
	int l = strlen(str);
	trie_t *p = root;
	for (int i = 0; i < l; ++i) {
		int ch = str[i]; // fixed to [0, C - 1], C = |SIGMA|
		if (!p->child[ch]) p->child[ch] = new_trie();
		p = p->child[ch];
	}
	p->flag = true;
}

void build() {
	queue<trie_t *> q;
	q.push(root);
	while (!q.empty()) {
		trie_t *p = q.front(), *t;
		q.pop();
		for (int i = 0; i < C; ++i) {
			t = p->fail;
			while (t && !t->child[i]) t = t->child[i];
			t = !t ? root : t->child[i];
			if (p->child[i]) {
				p->child[i]->fail = t;
				p->child[i]->flag |= t->flag;
				q.push(p->child[i]);
			} else p->child[i] = t;
		}
	}
}