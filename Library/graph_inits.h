struct edge {
	int from, to;
	ll cost;
	ll capa;

	edge(int s, int d) : from(s), to(d) {
		cost = 1; capa = 0;
	}
	edge(int s, int d, ll w) : from(s), to(d), cost(w) { capa = 0; }
	edge(int s, int d, ll x, ll y) :from(s), to(d), cost(x), capa(y) {  }

	bool operator < (const edge& x) const {
		return cost < x.cost;
	}
};
using graph = vector<vector<edge>>;

void add_edge(vector<vector<edge>> &g, int a, int b, ll cost = 1, ll cap = 0) {
	g[a].emplace_back(a, b, cost, cap);
	g[b].emplace_back(b, a, cost, cap);
}
