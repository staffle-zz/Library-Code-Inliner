mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll x = 0, ll y = INF) {
    return (rng() % (y - x + 1)) + x;
};