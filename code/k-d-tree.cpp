// scnt: the number of target points
// sp: the point to search the closest target points
const int DIM = 5;
int n, d, scnt;
struct point_t {
	int x[DIM];
} points[maxn], sp;
struct node_t {
	int sd;
	node_t *l, *r;
} node[maxn], *root;
struct cmp_t {
	int dd;
	bool operator()(const point_t &a, const point_t &b) {
		return a.x[dd] < b.x[dd];
	}
} cmp[DIM];

int dist2(const point_t &a, const point_t &b) {
	int res = 0;
	for (int i = 0; i < d; ++i) {
		res += (b.x[i] - a.x[i]) * (b.x[i] - a.x[i]);
	}
	return res;
}

struct cmp2_t {
	bool operator()(const point_t &a, const point_t &b) {
		return dist2(a, sp) < dist2(b, sp);
	}
};
priority_queue<point_t, vector<point_t>, cmp2_t> pq;

node_t *build(int dd, int l, int r) {
	if (l > r) return NULL;
	sort(points + l, points + 1 + r, cmp[dd]);
	int mid = (l + r) / 2;
	node[mid].l = build((dd + 1) % d, l, mid - 1);
	node[mid].r = build((dd + 1) % d, mid + 1, r);
	node[mid].sd = dd;
	return &node[mid];
}

void search(node_t *nd) {
	int sd = nd->sd, p = nd - node;
	pq.push(points[p]);
	while (pq.size() > scnt) pq.pop();
	int d2 = (sp.x[sd] - points[p].x[sd]) * (sp.x[sd] - points[p].x[sd]);
	if (sp.x[sd] < points[p].x[sd]) {
		if (nd->l) search(nd->l);
		if (nd->r && (pq.size() < scnt || dist2(sp, pq.top()) >= d2)) search(nd->r);
	} else {
		if (nd->r) search(nd->r);
		if (nd->l && (pq.size() < scnt || dist2(sp, pq.top()) >= d2)) search(nd->l);
	}
}

void init() {
	for (int i = 0; i < DIM; ++i) cmp[i].dd = i;
	root = build(0, 1, n);
}