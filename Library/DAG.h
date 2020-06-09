class DAG {
private:
	int n;
	vector<vector<edge>> g;
	vector<int> visited;
	vector<int> dp;
	vector<int> topological;

	int dfs(int s) {
		if ((int)g[s].size() == 0) {
			return 1;
		}
		if (dp[s] > 0) { return dp[s]; }

		int mx = 1;
		for (auto j : g[s]) {
			if (visited[j.to] == 0) {
				visited[j.to] = 1;
				int l = 0;
				l = dfs(j.to);
				chmax(mx, l);
			}
			else {
				chmax(mx, dp[j.to]);
			}
		}
		return dp[s] = mx + 1;
	}
public:
	DAG(const vector<vector<edge>> &f) {
		g = f;
		n = f.size();
		resize(visited, n + 1);
		fill(visited.begin(), visited.end(), 0);
		resize(dp, n + 1);
		fill(dp.begin(), dp.end(), -1);
		resize(topological, n);
	}
	DAG(int x) {
		n = x;
		resize(g, n);
		resize(visited, n + 1);
		fill(visited.begin(), visited.end(), 0);
		resize(dp, n + 1);
		fill(dp.begin(), dp.end(), -1);
	}

	void add_edge(int a, int b) {
		g[a].emplace_back(a, b);
	}
	void add_edge(int a, int b, ll c) {
		g[a].emplace_back(a, b, c);
	}
	void add_edge(int a, int b, ll c, ll d) {
		g[a].emplace_back(a, b, c, d);
	}

	int longest_path() {
		int mx = -1;
		for (int i = 0; i < n; i++) {
			int h = 0;
			if (visited[i] == 0) {
				h = dfs(i);
				chmax(mx, h);
			}
		}
		return mx - 1;
	}

	bool TopologicalSort() {
		int k = 0;
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
				if (--in[e.to] == 0) { q.push(e.to); }
			}
		}
		topological = ord;
		if (*max_element(in.begin(), in.end()) == 0) { return true; }
		return false;
	}

};