class Lca {
private:
	int n;
	int log2_n;
	vector<vector<int>> parent;
	vector<int> depth;

	void dfs(const vector<vector<edge>> &g, int v, int p, int d) {
		parent[0][v] = p;
		depth[v] = d;
		for (auto &e : g[v]) {
			if (e.to != p) { dfs(g, e.to, v, d + 1); }
		}
	}
public:

	Lca(const vector<vector<edge>> &g, int root) {
		n = g.size();
		log2_n = (int)log2(n) + 1;
		resize(parent, log2_n, n);
		resize(depth, n);

		dfs(g, root, -1, 0);

		for (int k = 0; k + 1 < log2_n; k++) {
			for (int v = 0; v < (int)g.size(); v++) {
				if (parent[k][v] < 0) {
					parent[k + 1][v] = -1;
				}
				else {
					parent[k + 1][v] = parent[k][parent[k][v]];
				}
			}
		}

	}

	int get_lca(int u, int v) {
		if (depth[u] > depth[v]) { swap(u, v); }//u≦v

		for (int k = 0; k < log2_n; k++) {
			if ((depth[v] - depth[u]) >> k & 1) {
				v = parent[k][v];
			}
		}
		if (u == v) { return u; }

		for (int k = log2_n - 1; k >= 0; k--) {
			if (parent[k][u] != parent[k][v]) {
				u = parent[k][u];
				v = parent[k][v];
			}
		}
		return parent[0][u];
	}

	int get_depth(int v) {
		return depth[v];
	}
};