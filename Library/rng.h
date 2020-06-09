#require ll infinity
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll x = -INF, ll y = INF) {
  return uniform_int_distribution<ll>(x, y)(rng);
}
