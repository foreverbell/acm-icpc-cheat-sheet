LL determinant() {
	LL result = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			while (det[j][i]) {
				LL ratio = det[i][i] / det[j][i];
				for (int k = i; k <= n; ++k) {
					det[i][k] -= ratio * det[j][k];
					swap(det[i][k], det[j][k]);
				}
				result = -result;
			}
		}
		result = result * det[i][i];
	}
	return result;
}