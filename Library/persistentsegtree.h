using Data = int; using Lazy = int; const Data vid = 0, qid = 0; const Lazy lid = -1;
template <const int MXSZ, const int MAXROOTS, const bool INDEXING> struct AdvanceSegTree {
    Data merge(const Data &l, const Data &r) { 
        return l + r; 
    }
    Data apply(const Data &x, const Lazy &v){
        return v;
    }
    Lazy getSegmentVal(const Lazy &v, int len){
        return v * len;
    }
    Lazy mergeLazy(const Lazy &l, const Lazy &r){ 
        return r;
    }
    int N, roots[MAXROOTS], L[MXSZ], R[MXSZ]; Data VAL[MXSZ], LZ[MXSZ], curNode = 0, curRoot = 0;
    int newNode(int cp = 0) {
        assrt(curNode < MXSZ);
        L[curNode] = curNode ? L[cp] : 0; 
        R[curNode] = curNode ? R[cp] : 0;
        VAL[curNode] = curNode ? VAL[cp] : vid; LZ[curNode] = curNode ? LZ[cp] : lid; 
        return curNode++;
    }
    void propagate(int cur, int cL, int cR) {
        if (LZ[cur] != lid) {
            int m = cL + (cR - cL) / 2;
            if (!L[cur]) 
                L[cur] = newNode();
    //           [cL,cR]
    //           /     \
    //       [cL,m]   [m+1,cR]
            VAL[L[cur]] = apply(VAL[L[cur]], getSegmentVal(LZ[cur], m - cL + 1)); 
            LZ[L[cur]] = mergeLazy(LZ[L[cur]], LZ[cur]);
            if (!R[cur]) 
                R[cur] = newNode();
            VAL[R[cur]] = apply(VAL[R[cur]], getSegmentVal(LZ[cur], cR - m)); 
            LZ[R[cur]] = mergeLazy(LZ[R[cur]], LZ[cur]);
            LZ[cur] = lid;
        }
    }
    template <class It> int build(int cL, int cR, It st) {
        int ret = newNode();
        if (cL == cR){ 
            VAL[ret] = *(st + cL - INDEXING);
            return ret; 
        }
        int m = cL + (cR - cL) / 2;
        L[ret] = build(cL, m, st); 
        R[ret] = build(m + 1, cR, st);
        VAL[ret] = merge(VAL[L[ret]], VAL[R[ret]]); 
        return ret;
    }
    int update(int cur, int cL, int cR, int l, int r, const Lazy &val, bool persistent) {
        if (cL > r || cR < l) 
            return cur;
        int ret = persistent ? newNode(cur) : cur;
        if (cL >= l && cR <= r) {
            VAL[ret] = apply(VAL[ret], getSegmentVal(val, cR - cL + 1));
            LZ[ret] = mergeLazy(LZ[ret], val); 
            return ret;
        }
        if (!L[ret]) 
            L[ret] = newNode();
        if (!R[ret]) 
            R[ret] = newNode();
        int m = cL + (cR - cL) / 2; 
        propagate(ret, cL, cR);
        L[ret] = update(L[ret], cL, m, l, r, val, persistent);
        R[ret] = update(R[ret], m + 1, cR, l, r, val, persistent);
        if (L[ret] && R[ret])
            VAL[ret] = merge(VAL[L[ret]], VAL[R[ret]]);
        else if (L[ret]) // right child does not exist
            VAL[ret] = merge(VAL[L[ret]], Data(vid));
        else if (R[ret]) // left child does not exist
            VAL[ret] = merge(VAL[R[ret]], Data(vid));
        return ret;
    }
    Data query(int cur, int cL, int cR, int l, int r) {
        if (cL > r || cR < l) 
            return qid;
        if (!cur) // node does not exist.
            return vid;
        if (cL >= l && cR <= r) 
            return VAL[cur];
        int m = cL + (cR - cL) / 2;
        propagate(cur, cL, cR);
        return merge(query(L[cur], cL, m, l, r), query(R[cur], m + 1, cR, l, r));
    }
    template <class It> void init(It st, It en){ 
        N = en - st; 
        newNode(); 
        roots[curRoot++] = build(INDEXING, N - !INDEXING, st); 
    }
    void init(int size) { 
        N = size; 
        newNode(); 
        roots[curRoot++] = newNode(); 
    }
    void update(int l, int r, Lazy val, bool persistent = false) {
        int nr = update(roots[curRoot - 1], INDEXING, N - !INDEXING, l, r, val, persistent);
        if (persistent) 
            roots[curRoot++] = nr;
        else 
            roots[curRoot - 1] = nr;
    }
    Data query(int l, int r, int rootInd = -1) {
        return query((rootInd == -1 ? roots[curRoot - 1] : roots[rootInd]), INDEXING, N - !INDEXING, l, r);
    }
    void revert(int x) { roots[curRoot++] = roots[x]; }
    void clear() { curNode = curRoot = 0; }
};