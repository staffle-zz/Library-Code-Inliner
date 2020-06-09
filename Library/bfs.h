void bfs(int src) {
    deque<int> q;
    q.push(src);
    vis[src] = 1;
    while (not q.empty()){
        int u = q.front();
        q.pop_front();
        for(int v : g[u]) {
            if(!vis[v]){
                vis[v] = 1;
                q.push_back(v);
            }
        }
    }
}