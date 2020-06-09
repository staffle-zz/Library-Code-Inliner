class MinimumCostFlow {
private:

	using Flow = ll;
	using Cost = ll;
	struct Edge {
		int d;
		Flow c, f;
		Cost w;
		int r, is_r;
		Edge(int d_, Flow c_, Flow f_, Cost w_, int r_, bool is_r_)
			: d(d_), c(c_), f(f_), w(w_), r(r_), is_r(is_r_) {}
	};
	int n;
	vector<vector<Edge>> g;

public:

	MinimumCostFlow(int n_) : n(n_), g(vector<vector<Edge>>(n_)) {}

	void add_edge(int src, int dst, Flow cap, Cost cost) {  // 有向辺
		int rsrc = g[dst].size();
		int rdst = g[src].size();
		g[src].emplace_back(dst, cap, 0, cost, rsrc, false);
		g[dst].emplace_back(src, cap, cap, -cost, rdst, true);
	}

	Cost solve(int s, int t, Flow f) {
		Cost res = 0;

		vector<Cost> h(n + 10), dist(n);
		vector<int> prevv(n + 10), preve(n + 10);

		using pcv = pair<Cost, int>;
		priority_queue<pcv, vector<pcv>, greater<pcv> > q;
		fill(h.begin(), h.end(), 0);
		while (f > 0) {
			fill(dist.begin(), dist.end(), LONGINF);
			dist[s] = 0;
			q.emplace(0, s);
			while (q.size()) {
				Cost cd;
				int v;
				tie(cd, v) = q.top();
				q.pop();
				if (dist[v] < cd) continue;
				for (int i = 0; i < (int)(g[v].size()); ++i) {
					Edge &e = g[v][i];
					if (residue(e) == 0) continue;
					if (dist[e.d] + h[e.d] > cd + h[v] + e.w) {
						dist[e.d] = dist[v] + e.w + h[v] - h[e.d];
						prevv[e.d] = v;
						preve[e.d] = i;
						q.emplace(dist[e.d], e.d);
					}
				}
			}

			if (dist[t] == LONGINF) return -1;  // 経路が見つからなかった

			// s-t 間を最短路に沿って目一杯流す
			for (int i = 0; i < n; ++i) h[i] += dist[i];
			Flow d = f;
			for (int v = t; v != s; v = prevv[v]) {
				chmin(d, residue(g[prevv[v]][preve[v]]));
			}
			f -= d;
			res += d * h[t];
			for (int v = t; v != s; v = prevv[v]) {
				Edge &e = g[prevv[v]][preve[v]];
				e.f += d;
				g[v][e.r].f -= d;
			}
		}
		return res;
	}

	Flow residue(const Edge &e) { return e.c - e.f; }

	// 流量を表示
	void show() {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < (int)(g[i].size()); ++j) {
				Edge &e = g[i][j];
				if (e.is_r) continue;
				cout << i << "->" << e.d << "(flow:" << e.f << ")" << endl;
			}
		}
	}
};