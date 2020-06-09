const int mx = 15000005;
struct Node {
    int left,right;
    int v , lazy;
    
} tr[mx];
class seg_tree {
public:
    int cn = 0;
    int newNode(){
        cn++;
        tr[cn].lazy = -1;
        return cn;
    }
    int root = 0;
    int n, n0;
    int merge(const int &l, const int &r) { 
        return l + r; 
    }
    int apply(const int &x, const int &v){
        return v;
    }
    int getSegmentVal(const int &v, int len){
        return v * len;
    }
    int mergeLazy(const int &l, const int &r){ 
        return r;
    }
    void push(int cur, int cL, int cR) {
        if (tr[cur].lazy != -1) {
            int m = cL + (cR - cL) / 2;
            if (tr[cur].left == 0) 
                tr[cur].left = newNode();
 
            tr[tr[cur].left].v = apply(tr[tr[cur].left].v , getSegmentVal(tr[cur].lazy, m - cL + 1)); 
            tr[tr[cur].left].lazy = mergeLazy(tr[tr[cur].left].lazy, tr[cur].lazy);
            if (tr[cur].right == 0) 
                tr[cur].right = newNode();
            tr[tr[cur].right].v = apply( tr[tr[cur].right].v, getSegmentVal(tr[cur].lazy, cR - m)); 
            tr[tr[cur].right].lazy = mergeLazy(tr[tr[cur].right].lazy, tr[cur].lazy);
            tr[cur].lazy = -1;
        }
    }
    int query(int a, int b, int n, int l, int r) {
        if (r <= a || b <= l) {
            return 0;
        }
        if(n==0)
            return 0;
        if (a <= l && r <= b) {
            return tr[n].v;
        }
        push(n,l,r);
        int lv = tr[n].left ? query(a, b, tr[n].left, l, (l + r) >> 1) : 0;
        int rv = tr[n].right ? query(a, b, tr[n].right, (l + r) >> 1, r) : 0;
        return (lv + rv);
    }
 
 
    seg_tree(int n) : n(n) {
        n0 = 1;
        // while (n0 < n) n0 <<= 1;
        n0 = n+1;
        root = newNode();
    }
    ~seg_tree() {
        root = 0;
    }
 
    void update(int cur, int cL, int cR, int l, int r, const int &val) {
        if (cL > r || cR < l) 
            return;
        if (cL >= l && cR <= r) {
            tr[cur].v = apply(tr[cur].v, getSegmentVal(val, cR - cL + 1));
            tr[cur].lazy = mergeLazy(tr[cur].lazy, val); 
            return;
        }
        if (tr[cur].left == 0) 
            tr[cur].left = newNode();
        if (tr[cur].right == 0) 
            tr[cur].right = newNode();
        int m = cL + (cR - cL) / 2; 
        push(cur, cL, cR);
        update(tr[cur].left, cL, m, l, r, val);
        update(tr[cur].right, m + 1, cR, l, r, val);
        tr[cur].v = merge(tr[tr[cur].left].v , tr[tr[cur].right].v);
    }
    void update(int l,int r,int val){
        update(root,0,n0,l,r,val);
    }
    int query(int a, int b) {
        return query(a, b, root, 0, n0);
    }
 
    int lquery(int b) {
        return query(0, b, root, 0, n0);
    }
 
    int rquery(int a) {
        return query(a, n0, root, 0, n0);
    }
};