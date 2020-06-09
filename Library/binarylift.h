struct binarylift{
    int n, root, lg;
    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    binarylift(int n_, int root){
        n = n_, root = root, lg = ceil(log2(n)), depth.resize(n,0), up.assign(n, vector<int>(lg + 1));
        adj.resize(n);
    }
    void insert(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init(){
        dfs(root, root);
    }
    void dfs(int u, int p){
        up[u][0] = p;
        for(int i = 1; i <= lg; i ++){
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        for(auto &v: adj[u]) if(v != p){
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    int lca(int u, int v){
        if(depth[u] < depth[v]){
            swap(u, v);
        }
        u = trace_up(u, depth[u] - depth[v]);
        for(int d = lg; d >= 0; d --){
            if(up[u][d] != up[v][d]){
                u = up[u][d], v = up[v][d];
            }
        }
        return u == v ? u : up[u][0];
    }
    int dist(int u, int v){
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
    int trace_up(int u, int dist){
        if(dist >= depth[u] - depth[root]){
            return root;
        }
        for(int d = lg; d >= 0; d --){
            if(dist & (1 << d)) u = up[u][d];
        }
        return u;
    }
};