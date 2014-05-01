void tarjan(int u) {
	int v;
	dfn[u] = low[u] = ++ind;
	sk.push(u), instack[u] = true; 
	for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
		v = *it; // Check if v is the parent of u(BCC)
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			// Check BCC here
			// Cut vertex: Pop stack until v is poped, then add u.
		} else if (instack[v]) { // ! instack[v] -> else
			low[u] = min(low[u], dfn[v]);
		}
	}
	/* Check SCC here
	if (dfn[u] == low[u]) {
		++color;
		do {
			v = sk.top(), instack[v] = false;
			sk.pop();
			block[v] = color;
		} while (v != u);
	} */
}