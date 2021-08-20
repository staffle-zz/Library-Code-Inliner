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

bool solve() {
    int n, k;
    cin >> n >> k;
    ll ans = MOD;
    int found = 0 , cur = n;
    while(1){
        string S = to_string(cur);
        set<char> s(all(S));
        if(sz(s) <= k){
            return cout << cur << endl , 0;
        }
        cur++;
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(NULL);
    int Tests = 1;
    cin >> Tests;
    while (Tests--)
        solve();
}
