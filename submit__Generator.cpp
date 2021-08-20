#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#define dbg(...)
#define db(...)

#include "bits/stdc++.h"
using namespace std;
using ll = long long;

#define len(x) ((int)x.size())
#define F first
#define S second
#define all(x) begin(x), end(x)
#define endl '\n'
#define bit(x, i) ((x >> i) & (1))
const int MOD = 1e9 + 7;
const int N = 5e5 + 5;


bool solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k, 0), t(n, 2 * MOD);

    set<pair<int, int>> cur;

    for (int i = 0; i < k; i++)
        cin >> a[i], a[i]--;
    for (int i = 0, x; i < k; i++)
        cin >> x, t[a[i]] = x, cur.insert({x, a[i]});

    while (!cur.empty()) {
        auto [tem, room] = *cur.begin();
        cur.erase(cur.begin());
        if (t[room] < tem)
            continue;
        if (room != 0 and t[room - 1] > tem + 1) {
            t[room - 1] = tem + 1;
            cur.insert({tem + 1, room - 1});
        }
        if (room != n - 1 and t[room + 1] > tem + 1) {
            t[room + 1] = tem + 1;
            cur.insert({tem + 1, room + 1});
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << t[i] << " ";
    }
    return cout << endl, 0;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(ios::badbit | ios::failbit);
    int tests = 1;
    cin >> tests;
    while (tests--)
        solve();
}