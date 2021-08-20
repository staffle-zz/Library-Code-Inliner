/**
* author  : amit_dwivedi
* created : Fri Aug 20 16:11:13 2021
**/
#include "bits/stdc++.h"
using namespace std;
using ll = long long;


template <class T>
struct cordinate_compress {
    vector<T *> val;
    unordered_map<int, T> actual;
    void push_back(T &x) {
        val.push_back(&x);
    }

    T operator()(T init = T()) {
        sort(val.begin(), val.end(), [](int *x, int *y) { return *x < *y; });
        T last = 0, q = 0;
        for (size_t i = 0; i < val.size(); i++) {
            if (!i || *val[i] != last) {
                q++;
                actual.insert({*val[i], q - 1 + init});
            }
            last = *val[i];
            *val[i] = q - 1 + init;
        }
        return q;
    }
};

struct seg {
    int l, r, t;

    template <class T>
    bool operator<(const T &b) const {
        return l < b.l;
    }
};

// fix type of val here to avoid overflow.
struct updater {
    bool issetter;
    ll val;

    updater operator+(const updater &b) const {
        if (!b.issetter) {
            return {issetter, val + b.val};
        } else {
            return b;
        }
    }
};

template <class T, class U, class F, class G, class H>
struct segtreelazy {
    struct node {
        T val;
        U upd;
    };
    int SZ;
    vector<node> a;
    T qID;    // Neutral element
    U uID;    // Neutral update
    F merge;  // Add two elements
    G g;      // Add two updaters
    H h;      // Add an element and an update

    // Bottom level element
    segtreelazy(int n, F merge, G g, H h, T qID = T(), U uID = U(), T ID = T())
        : qID(qID), uID(uID), merge(merge), g(g), h(h) {
        SZ = 1;
        while (SZ < n) SZ <<= 1;
        a.assign(2 * SZ, node{ID, uID});
        for (int i = SZ - 1; i; i--) a[i].val = merge(a[2 * i].val, a[2 * i + 1].val);
    }

    void push(int x, int l, int r) {
        a[x].val = h(a[x].val, a[x].upd);
        if (x < SZ) {
            a[2 * x].upd = g(a[2 * x].upd, a[x].upd);
            a[2 * x + 1].upd = g(a[2 * x + 1].upd, a[x].upd);
        }
        a[x].upd = uID;
    }

    void update(int l, int r, const U &upd, int x, int xl, int xr) {
        if (r <= xl || xr <= l)
            return push(x, xl, xr);
        if (l <= xl && xr <= r)
            return a[x].upd = g(a[x].upd, upd), push(x, xl, xr);
        push(x, xl, xr);
        int xm = (xl + xr) >> 1;
        update(l, r, upd, 2 * x, xl, xm);
        update(l, r, upd, 2 * x + 1, xm, xr);
        a[x].val = merge(a[2 * x].val, a[2 * x + 1].val);
    }

    T get(int l, int r, int x, int xl, int xr) {
        push(x, xl, xr);
        if (r <= xl || xr <= l)
            return qID;
        if (l <= xl && xr <= r)
            return a[x].val;
        int xm = (xl + xr) >> 1;
        return merge(get(l, r, 2 * x, xl, xm), get(l, r, 2 * x + 1, xm, xr));
    }

    void update(int l, int r, const U &upd) {
        update(l, r, upd, 1, 0, SZ);
    }

    void modify(int l, int r, T delta) {
        update(l, r, U{false, delta});
    }
    void set(int l, int r, T delta) {
        update(l, r, U{true, delta});
    }

    T operator()(int l, int r) {
        return get(l, r, 1, 0, SZ);
    }
};


int n;
seg a[200005];
const int inf = 100;

int main() {
    ios::sync_with_stdio(!cin.tie(0));
    int n;
    cin >> n;

    int w = 2 * n + 5;
    cordinate_compress<int> c;

    for (int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r >> a[i].t;
        c.push_back(a[i].l);
        c.push_back(a[i].r);
    }

    c(1);

    for (int i = 0; i < n; ++i) {
        cout << a[i].l << " " << a[i].r << " " << a[i].t << endl;
    }
    sort(a, a + n);

    for (int i = 0; i < n; ++i) {
        cout << a[i].l << " " << a[i].r << " " << a[i].t << endl;
    }
    segtreelazy d1(
        w,
        [](int x, int y) { return max(x, y); },
        plus<updater>(),
        [](int x, updater upd) { return upd.issetter ? upd.val : x + upd.val; },
        -inf,
        updater{false, 0},
        -inf);

    d1.update(0, 1, updater{true, 0});

    auto d2 = d1;


    for (int i = 0; i < n; i++) {
        auto [l, r, t] = a[i];
        if (t == 1) {
            // int v1 = d1(0, w);
            int v1p = d1(0, r + 1);
            int v2 = d2(0, l);
            d1.update(r + 1, w, updater{false, 1});
            d1.update(r, r + 1, updater{true, max(v1p, v2) + 1});
        } else {
            // int v2 = d2(0, w);
            int v2p = d2(0, r + 1);
            int v1 = d1(0, l);
            d2.update(r + 1, w, updater{false, 1});
            d2.update(r, r + 1, updater{true, max(v2p, v1) + 1});
        }

        // for (int i=0; i<w; i++) cerr << d1(i, i+1) << " \n"[i == w-1];
        // for (int i=0; i<w; i++) cerr << d2(i, i+1) << " \n"[i == w-1];
        // cerr << '\n';
    }

    cout << max(d1(0, w), d2(0, w)) << '\n';
}
