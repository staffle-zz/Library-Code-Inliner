class seg_tree {
private:
	int n;
	ll inf = (1LL << 31) - 1;//2^31-1
	vector<ll> dat, lazy;

	void eval(int len, int k) {
		if (lazy[k] == inf) return;
		if (k * 2 + 1 < n * 2 - 1) {
			lazy[2 * k + 1] = lazy[k];
			lazy[2 * k + 2] = lazy[k];
		}
		dat[k] = lazy[k];
		lazy[k] = inf;
	}
public:
	seg_tree() {}
	seg_tree(int n_) {
		n = 1; while (n < n_) n *= 2;
		dat.assign(n * 2, inf);
		lazy.assign(n * 2, inf);
	}

	// [a, b)
	ll update(int a, int b, ll x, int k, int l, int r) {
		eval(r - l, k);
		if (b <= l || r <= a) return dat[k];
		if (a <= l && r <= b) {
			lazy[k] = x;
			return lazy[k];
		}
		return dat[k] = min(update(a, b, x, 2 * k + 1, l, (l + r) / 2), update(a, b, x, 2 * k + 2, (l + r) / 2, r));
	}
	ll update(int a, int b, ll x) { return update(a, b, x, 0, 0, n); }

	// [a, b)
	ll query(int a, int b, int k, int l, int r) {
		eval(r - l, k);
		if (b <= l || r <= a) return inf;
		if (a <= l && r <= b) return dat[k];
		ll vl = query(a, b, 2 * k + 1, l, (l + r) / 2);
		ll vr = query(a, b, 2 * k + 2, (l + r) / 2, r);
		return min(vl, vr);
	}
	ll query(int a, int b) { return query(a, b, 0, 0, n); }
};