vector<ll> Prefix_sum(const vector<ll> &v) {
	int n = v.size();
	vector<ll> a(n, 0);
	a[0] = v[0];
	for (int i = 1; i < n; i++) {
		a[i] += a[i - 1] + v[i];
	}
	return a;
}