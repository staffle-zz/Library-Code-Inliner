/**
 * author  : amit_dwivedi
 * created : Fri Jan 08 20:53:30 2021
 **/
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
using ld = long double;

#define _(_1, _2, _3, _4, NAME, ...) NAME
#define f3(i, a, b, inc) for (ll i = (a); (inc) > 0 ? i <= (b) : i >= (b); i += (inc))
#define f2(i, a, b) f3(i, a, b, 1 - 2 * (a > b))
#define f1(i, n) f2(i, 0, n - 1)
#define f0(i) f2(i, 0, n - 1)
#define fr(...) _(__VA_ARGS__, f3, f2, f1, f0)(__VA_ARGS__)
#define fa(i, x) for (auto &i : x)
#define sz(x) ((int)x.size())
#define len(x) ((int)x.length())
#define F first
#define S second
#define all(x) begin(x), end(x)

const int N = 3e5 + 10;

const ll INF = 2e18;

const ll MOD = 1e9 + 7;

auto clk = clock();
mt19937_64 rang(chrono::high_resolution_clock::now().time_since_epoch().count());
int rng(int llim, int lim) {
    uniform_int_distribution<int> uid(llim, lim);
    return uid(rang);
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    n = rng(10, 100);
    k = rng(n + 1, 1000);
    string s;
    for (int i = 0; i < n; i++) s += char(rng(0, 25) + 'a');

    cout << n << " " << k << endl << s << endl;
    return 0;
}
