const int maxm = 325, maxk = 5001; 
// Attention: maxk(Number of 1 + Column Size) ought NOT be very LARGE
int pt, L[maxk], R[maxk], U[maxk], D[maxk], C[maxk], A[maxk], O[maxm], S[maxm], res[maxk]; 

void init(int m) { // m: Number of columns
	zm(L), zm(R), zm(U), zm(D), zm(C), zm(A), zm(O), zm(S), pt = m;
	for (int i = 0; i <= m; ++i) L[i] = i - 1, R[i] = i + 1, C[i] = D[i] = U[i] = i;
	L[0] = m, R[m] = 0;
}

void insert(int row, int *t, int total) { // t: Positions of 1
	for (int i = 1; i <= total; ++i) {
		int col = t[i];
		++S[col], ++pt;
		C[pt] = col, A[pt] = row, U[pt] = col, D[pt] = D[col];
		U[D[col]] = pt, D[col] = pt;
		if (i != 1) {
			L[pt] = pt - 1, R[pt] = pt - i + 1, R[pt - 1] = L[pt - i + 1] = pt;
		} else {
			L[pt] = R[pt] = pt;
		}
	}
}

void remove(int x) {
	L[R[x]] = L[x], R[L[x]] = R[x];
	for (int i = D[x]; i != x; i = D[i]) {
		for (int j = R[i]; j != i; j = R[j]) {
			U[D[j]] = U[j], D[U[j]] = D[j], --S[C[j]];
		}
	}
}

void resume(int x) {
	for (int i = U[x]; i != x; i = U[i]) {
		for (int j = L[i]; j != i; j = L[j]) {
			U[D[j]] = j, D[U[j]] = j, ++S[C[j]];
		}
	}
	L[R[x]] = x, R[L[x]] = x;
}

bool dlx(int k) { // Call dlx(0)
	if (R[0] == 0) {
		for (int i = 0; i < k; ++i) res[i] = O[i];
		return true;
	} else {
		int val = maxint, col = 0;
		for (int i = R[0]; i != 0; i = R[i]) {
			if (S[i] <= val) col = i, val = S[i];
		}
		if (val == 0) return false;
		remove(col);
		for (int i = D[col]; i != col; i = D[i]) {
			O[k] = A[i];
			for (int j = R[i]; j != i; j = R[j]) remove(C[j]);
			if (dlx(k + 1)) return true;
			for (int j = L[i]; j != i; j = L[j]) resume(C[j]);
		}
		resume(col);
		return false;
	}
}