#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#define dbg(...)
#define db(...)

#include "bits/stdc++.h"

using namespace std;
using ll = long long;
const int N = 3e5;

int a[N], t[N];
int n;
vector<int> order;
void inorder(int c) {
    if (c >= n || t[c] == -1) return;

    inorder(2 * c + 1);
    order.push_back(t[c]);
    inorder(2 * c + 2);
}

int main() {
    ios::sync_with_stdio(false), cin.tie(NULL);
    cin >> n;

    for (int i = 0; i < n; i++) cin >> t[i];

    inorder(0);

    int ans = 0;
    for (int i = 0; i < order.size(); i++) {
        ans = 0;
        if (i - 1 >= 0) ans += order[i - 1];
        if (i + 1 < order.size()) ans += order[i + 1];
        cout << ans << " ";
    }
    cout << endl;
}