class BipartiteMatching {
private:
	int V;
	vector<int> match;
	vector<bool> used;
	vector<vector<int>> g;
	vector<pair<int, int>> match_pair;

	bool dfs(int v) {
		used[v] = true;
		for (int i = 0; i < (int)g[v].size(); i++) {
			int u = g[v][i];
			int w = match[u];
			if (w < 0 || !used[w] && dfs(w)) {
				match[v] = u;
				match[u] = v;
				match_pair.emplace_back(make_pair(u, v));
				return true;
			}
		}
		return false;
	}

public:
	BipartiteMatching(int n) {
		V = n;
		resize(match, n);
		resize(used, n);
		resize(g, n);
	}

	void add_edge(int u, int v) {
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}

	int MatchingSolve() {
		int res = 0;
		fill(match.begin(), match.end(), -1);

		for (int v = 0; v < V; v++) {
			if (match[v] < 0) {
				fill(used.begin(), used.end(), false);
				if (dfs(v)) {
					res++;
				}
			}
		}
		return res;
	}

	vector<pair<int, int>> get_pair() {
		for (auto x : match_pair) {
			cout << x.first << "  " << x.second << endl;
		}
		return match_pair;
	}

};