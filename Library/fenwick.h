class fenwick {
public:
	vector<ll> bit0, bit1;
	int n;

	ll sum(const vector<ll> &b, int i) {
		ll s = 0;
		while (i > 0) {
			s += b[i];
			i -= (i&-i);
		}
		return s;
	}

	void add(vector<ll> &b, int i, ll v) {
		while (i <= n) {
			b[i] += v;
			i += (i&-i);
		}
	}

	fenwick() {}
	fenwick(int N) {
		n = N;
		resize(bit0, n + 1);
		resize(bit1, n + 1);
		fill(bit0.begin(), bit0.end(), 0);
		fill(bit1.begin(), bit1.end(), 0);
	}

	void update(int l, int r, ll x) {
		add(bit0, l, -x * (l - 1));
		add(bit1, l, x);
		add(bit0, r + 1, x*r);
		add(bit1, r + 1, -x);
	}

	ll query(int l, int r) {
		ll res = 0;
		res += sum(bit0, r) + sum(bit1, r)*r;
		res -= sum(bit0, l - 1) + sum(bit1, l - 1)*(l - 1);
		return res;
	}
};
