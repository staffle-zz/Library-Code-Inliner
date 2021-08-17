#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#define dbg(...)
#define db(...)

#include "bits/stdc++.h"
using namespace std;
using ll = long long;

#define sz(x) ((int)x.size())
#define F first
#define S second
#define all(x) begin(x), end(x)
#define endl '\n'

const int MOD = 7 + 1e9;
const int N = 5 + 5e4;

void solve() {
    int n, k;
    string s;
    cin >> n >> k >> s;
    string ans(k, s[0]);

    for (int len = 1; len <= n; len++) {
        string temp;
        for (int i = 0; i < k; i++) {
            temp += s[i % len];
        }
        if (temp < ans) {
            ans = temp;
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(NULL);
    int Tests = 1;
    // cin >> Tests;
    while (Tests--)
        solve();
}
