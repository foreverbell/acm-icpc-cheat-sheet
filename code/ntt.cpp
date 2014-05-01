const int P = 1000003; // Approximate 10^6
const int P1 = 998244353, P2 = 995622913;
const LL M1 = 397550359381069386LL, M2 = 596324591238590904LL;
const LL MM = 993874950619660289LL;

int CRT(int x1, int x2) {
	return (mult(M1, x1, MM) + mult(M2, x2, MM)) % MM % P; // 64bit multiplication
}

void NTT(int *A, int PM, int PW, int n) {
	for (int m = n, h; h = m / 2, m >= 2; PW = (LL)PW * PW % PM, m = h) {
		for (int i = 0, w = 1; i < h; ++i, w = (LL)w * PW % PM) {
			for (int j = i; j < n; j += m) {
				int k = j + h, x = (A[j] - A[k] + PM) % PM;
				A[j] += A[k]; A[j] %= PM;
				A[k] = (LL)w * x % PM;
			}
		}
	}
	for (int i = 0, j = 1; j < n - 1; ++j) {
		for (int k = n / 2; k > (i ^= k); k /= 2);
		if (j < i) swap(A[i], A[j]);
	}
}

int E1, E2, F1, F2, I1, I2;
int init(int n) { // assert(k <= 19);
	int k = 1, N = 2, p;
	while (N < n) N <<= 1, ++k;
	p = 7 * 17; for (int i = 1; i <= 23 - k; ++i) p *= 2;
	E1 = fpow(3, p, P1); F1 = fpow(E1, P1 - 2, P1); I1 = fpow(N, P1 - 2, P1);
	p = 9 * 211; for (int i = 1; i <= 19 - k; ++i) p *= 2;
	E2 = fpow(5, p, P2); F2 = fpow(E2, P2 - 2, P2); I2 = fpow(N, P2 - 2, P2);
	return N;
}

void mul(int *A, int *B, int *C, int n) {
	static int A1[maxn], B1[maxn], C1[maxn];
	int N = init(n);
	memset(A1, 0, sizeof(*A1) * N); memset(B1, 0, sizeof(*B1) * N); memset(C1, 0, sizeof(*C1) * N); 
	memset(C, 0, sizeof(*C) * N);
	memcpy(A1, A, sizeof(*A) * n); memcpy(B1, B, sizeof(*B) * n);
	NTT(A1, P1, E1, N); NTT(B1, P1, E1, N);
	for (int i = 0; i < N; ++i) C1[i] = (LL)A1[i] * B1[i] % P1;
	NTT(C1, P1, F1, N);
	for (int i = 0; i < N; ++i) C1[i] = (LL)C1[i] * I1 % P1;
	NTT(A, P2, E2, N); NTT(B, P2, E2, N);
	for (int i = 0; i < N; ++i) C[i] = (LL)A[i] * B[i] % P2;
	NTT(C, P2, F2, N);
	for (int i = 0; i < N; ++i) C[i] = (LL)C[i] * I2 % P2;
	for (int i = 0; i < N; ++i) C[i] = CRT(C1[i], C[i]);
	for (int i = n; i < N; ++i) C[i] = 0;
}