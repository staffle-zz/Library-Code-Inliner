bool TopologicalSort(const vector<vector<edge>> &g, vector<int> &ans) {
	int n = g.size(), k = 0;
	vector<int> ord(n), in(n);
	for (auto &es : g) {
		for (auto &e : es) {
			in[e.to]++;
		}
	}
	queue<int> q;
	for (int i = 0; i < n; ++i) {
		if (in[i] == 0) q.push(i);
	}
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		ord[k++] = v;
		for (auto &e : g[v]) {
			if (--in[e.to] == 0) q.push(e.to);
		}
	}
	ans = ord;
	if (*max_element(in.begin(), in.end()) == 0) { return true; }
	return false;
}