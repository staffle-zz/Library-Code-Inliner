#require MOD IO
struct mi {
  using T = decay<decltype(MOD)>::type;
  T v;
  explicit operator T() const { return v; }
  mi() { v = 0; }
  mi(ll _v) {
    v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
    if (v < 0) v += MOD;
  }
  friend bool operator==(const mi& a, const mi& b) { return a.v == b.v; }
  friend bool operator!=(const mi& a, const mi& b) { return !(a == b); }
  friend bool operator<(const mi& a, const mi& b) { return a.v < b.v; }
  friend ostream& operator<<(ostream& os, const mi& a) { return os << a.v; }
  friend void pr(const mi& m) { pr(m.v); }
  mi& operator+=(const mi& m) {
    if ((v += m.v) >= MOD) v -= MOD;
    return *this;
  }
  mi& operator-=(const mi& m) {
    if ((v -= m.v) < 0) v += MOD;
    return *this;
  }
  mi& operator*=(const mi& m) {
    v = (ll)v * m.v % MOD;
    return *this;
  }
  mi& operator/=(const mi& m) { return (*this) *= inv(m); }
  friend mi pow(mi a, ll p) {
    mi ans = 1;
    assert(p >= 0);
    for (; p; p /= 2, a *= a)
      if (p & 1) ans *= a;
    return ans;
  }
  friend mi inv(const mi& a) {
    assert(a.v != 0);
    return pow(a, MOD - 2);
  }
  mi operator-() const { return mi(-v); }
  mi& operator++() { return *this += 1; }
  mi& operator--() { return *this -= 1; }
  friend mi operator+(mi a, const mi& b) { return a += b; }
  friend mi operator-(mi a, const mi& b) { return a -= b; }
  friend mi operator*(mi a, const mi& b) { return a *= b; }
  friend mi operator/(mi a, const mi& b) { return a /= b; }
};
