#define _(_1, _2, _3, _4, NAME, ...) NAME
#define f3(i, a, b, inc) for (int i = (a) - (inc < 0); (inc) > 0 ? i < (b) : i >= (b); i += (inc))
#define f2(i, a, b) f3(i, a, b, 1 - 2 * (a > b))
#define f1(i, n) f2(i, 0, n)
#define f0(i) f2(i, 0, n)
#define fr(...) _(__VA_ARGS__, f3, f2, f1, f0)(__VA_ARGS__)
#define trav(i, x) for (auto& i : x)
#define sz(x) ((int)x.size())
#define len(x) ((int)x.length())
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
#define all(x) begin(x), end(x)

