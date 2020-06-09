#require INF
bool  WarshallFloyd(vector<vector<ll>> &c) {
	int V = c.size();
	for (int i = 0; i < V; i++) {
		c[i][i] = 0;
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			for (int k = 0; k < V; k++) {
				if (c[j][k] > c[j][i] + c[i][k]) {
					c[j][k] = c[j][i] + c[i][k];
				}
			}
		}
	}

	for (int i = 0; i < V; i++) {
		if (c[i][i] < 0) {
			return false;
		}
	}



	return true;
}
vector<ll> Dijkstra(int i, vector<vector<edge>> graph) {

	int n = graph.size();
	vector<ll> d(n, INF);
	d[i] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
	q.push(make_pair(0, i));
	while (!q.empty()) {
		pair<ll, int> p = q.top();
		q.pop();
		int v = p.second;
		if (d[v] < p.first) {
			continue;
		}
		for (auto x : graph[v]) {
			if (d[x.to] > d[v] + x.cost) {
				d[x.to] = d[v] + x.cost;
				q.push(make_pair(d[x.to], x.to));
			}
		}
	}
	return d;
}
bool BellmanFord(int start, int V, int E, vector<edge> Edge, vector<ll> &d) {
	resize(d, V);
	fill(d.begin(), d.end(), LONGINF);
	d[start] = 0;
	vector<bool> t(V, false);

	for (int i = 0; i < V - 1; i++) {
		for (int j = 0; j < E; j++) {
			edge e = Edge[j];
			if (d[e.from] == INF) { continue; }
			if (d[e.to] > d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;
			}
		}
	}

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < E; j++) {
			edge e = Edge[j];
			if (d[e.from] == INF) { continue; }
			if (d[e.to] > d[e.from] + e.cost) {
				d[e.to] = d[e.from] + e.cost;
				t[e.to] = true;
			}
			if (t[e.from]) {
				t[e.to] = true;
			}
		}
	}

	if (t[V - 1]) {
		return false;
	}

	return true;
}
