class Dinic {
#define FLOW int
private:
	int n, s, t;
	vector<int> level, prog, que;
	vector<vector<FLOW>> cap, flow;
	vector<vector<int>> g;
	FLOW inf;
public:
	Dinic(const vector<vector<edge>> &graph) :
		n(graph.size()),
		cap(n, vector<FLOW>(n)),
		flow(n, vector<FLOW>(n)),
		g(n, vector<int>()),
		inf(INF) {
		for (int i = 0; i < n; i++) {
			for (auto &e : graph[i]) {
				int u = e.from, v = e.to;
				ll c = e.capa;
				cap[u][v] += c;
				cap[v][u] += c;
				flow[v][u] += c;
				g[u].push_back(v);
				g[v].push_back(u);
			}
		}
	}
	inline FLOW residue(int u, int v) { return cap[u][v] - flow[u][v]; }
	FLOW solve(int s_, int t_) {
		this->t = t_, this->s = s_;
		que.resize(n + 1);
		FLOW res = 0;
		while (levelize()) {
			prog.assign(n, 0);
			res += augment(s, inf);
		}
		return res;
	}
	bool levelize() {
		int l = 0, r = 0;
		level.assign(n, -1);
		level[s] = 0;
		que[r++] = s;
		while (l != r) {
			int v = que[l++];
			if (v == t) break;
			for (const int &d : g[v])
				if (level[d] == -1 && residue(v, d) != 0) {
					level[d] = level[v] + 1;
					que[r++] = d;
				}
		}
		return level[t] != -1;
	}
	FLOW augment(int v, FLOW lim) {
		FLOW res = 0;
		if (v == t) return lim;
		for (int &i = prog[v]; i < (int)g[v].size(); i++) {
			const int &d = g[v][i];
			if (residue(v, d) == 0 || level[v] >= level[d]) continue;
			const FLOW aug = augment(d, min(lim, residue(v, d)));
			flow[v][d] += aug;
			flow[d][v] -= aug;
			res += aug;
			lim -= aug;
			if (lim == 0) break;
		}
		return res;
	}
};