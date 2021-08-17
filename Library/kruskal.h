#require ll uf

ll kruskal(int n, vector<vector<int>> ed) {
    UnionFind uf(n);
    sort(ed.begin(), ed.end());
    vector<int> mst;
    ll ans = 0, i = 0;
    while (i < ed.size() and uf.set_size > 1) {
        if (uf.find(ed[i][1]) != uf.find(ed[i][2])) {
            uf.unite(ed[i][1], ed[i][2]);
            mst.push_back(i);
            ans += ed[i][0];
        }
        i++;
    }
    return ans;
}