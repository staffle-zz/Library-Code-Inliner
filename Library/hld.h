template<class T, class BO1, class BO2, class BO3>
struct lazyseg{
    lazyseg *l = 0, *r = 0;
    int low, high;
    BO1 &lop;       // Lazy op(L, L -> L)
    BO2 &qop;       // Query op(Q, Q -> Q)
    BO3 &aop;       // Apply op(Q, L, len -> Q)
    vector<T> &id;  // Lazy id(L), Query id(Q), Disable constant(Q)
    T lset, lazy, val;
    lazyseg(int low, int high, BO1 &lop, BO2 &qop, BO3 &aop, vector<T> &id)
    : low(low), high(high), lop(lop), qop(qop), aop(aop), id(id){
        lazy = id[0], val = id[1], lset = id[2];
    }
    lazyseg(const vector<T> &arr, int low, int high, BO1 &lop, BO2 &qop, BO3 &aop, vector<T> &id)
    : low(low), high(high), lop(lop), qop(qop), aop(aop), id(id){
        lazy = id[0], lset = id[2];
        if(high - low > 1){
            int mid = low + (high - low) / 2;
            l = new lazyseg(arr, low, mid, lop, qop, aop, id);
            r = new lazyseg(arr, mid, high, lop, qop, aop, id);
            val = qop(l->val, r->val);
        }
        else val = arr[low];
    }
    void push(){
        if(!l){
            int mid = low + (high - low) / 2;
            l = new lazyseg(low, mid, lop, qop, aop, id);
            r = new lazyseg(mid, high, lop, qop, aop, id);
        }
        if(lset != id[2]){
            l->set(low, high, lset);
            r->set(low, high, lset);
            lset = id[2];
        }
        else if(lazy != id[0]){
            l->update(low, high, lazy);
            r->update(low, high, lazy);
            lazy = id[0];
        }
    }
    void set(int ql, int qr, T x){
        if(qr <= low || high <= ql) return;
        if(ql <= low && high <= qr){
            lset = x;
            lazy = id[0];
            val = aop(id[1], x, high - low);
        }
        else{
            push();
            l->set(ql, qr, x);
            r->set(ql, qr, x);
            val = qop(l->val, r->val);
        }
    }
    void update(int ql, int qr, T x){
        if(qr <= low || high <= ql) return;
        if(ql <= low && high <= qr){
            if(lset !=  id[2]) lset = lop(lset, x);
            else lazy = lop(lazy, x);
            val = aop(val, x, high - low);
        }
        else{
            push(), l->update(ql, qr, x), r->update(ql, qr, x);
            val = qop(l->val, r->val);
        }
    }
    T query(int ql, int qr){
        if(qr <= low || high <= ql) return id[1];
        if(ql <= low && high <= qr) return val;
        push();
        return qop(l->query(ql, qr), r->query(ql, qr));
    }
};
template<class DS, class BO, class T, int VALS_IN_EDGES = 0>
struct HLD{
    int N, root;
    vector<vector<int>> adj;
    vector<int> par, size, depth, next, pos, rpos;
    DS &tree;
    BO bin_op;
    const T id;
    HLD(int N, int root, DS &tree, BO bin_op, T id):
    N(N), root(root), adj(N), par(N, -1), size(N, 1), depth(N), next(N), pos(N), tree(tree), bin_op(bin_op), id(id){
        this->root = next[root] = root;
    }
    void insert(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs_sz(int u){
        if(par[u] != -1) adj[u].erase(find(all(adj[u]), par[u]));
        for(auto &v: adj[u]){
            par[v] = u, depth[v] = depth[u] + 1;
            dfs_sz(v);
            size[u] += size[v];
            if(size[v] > size[adj[u][0]]) swap(v, adj[u][0]);
        }
    }
    void dfs_hld(int u){
        static int t = 0;
        pos[u] = t ++;
        rpos.push_back(u);
        for(auto &v: adj[u]){
            next[v] = (v == adj[u][0] ? next[u] : v);
            dfs_hld(v);
        }
    }
    void init(){
        dfs_sz(root), dfs_hld(root);
    }
    template<class Action>
    void processpath(int u, int v, Action act){
        for(; next[u] != next[v]; v = par[next[v]]){
            if(depth[next[u]] > depth[next[v]]) swap(u, v);
 
            act(pos[next[v]], pos[v] + 1);
        }
        if(depth[u] > depth[v]) swap(u, v);
        act(pos[u] + VALS_IN_EDGES, pos[v] + 1);
    }
    void updatepath(int u, int v, T val, int is_update = true){
        if(is_update) processpath(u, v, [this, &val](int l, int r){tree.update(l, r, val);});
        else processpath(u, v, [this, &val](int l, int r){tree.set(l, r, val);});
    }
    void updatesubtree(int u, T val, int is_update = true){
        if(is_update) tree.update(pos[u] + VALS_IN_EDGES, pos[u] + size[u], val);
        else tree.set(pos[u] + VALS_IN_EDGES, pos[u] + size[u], val);
    }
    T querypath(int u, int v){
        T res = id;
        processpath(u, v, [this, &res](int l, int r){res = bin_op(res, tree.query(l, r));});
        return res;
    }
    T querysubtree(int u){
        return tree.query(pos[u] + VALS_IN_EDGES, pos[u] + size[u]);
    }
};