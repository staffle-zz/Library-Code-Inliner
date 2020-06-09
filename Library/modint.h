template<ll mod> struct ModInt {
	long long val;
	constexpr ModInt(long long v = 0) noexcept : val(v % mod) {
		if (val < 0) v += mod;
	}
	constexpr int getmod() { return mod; }
	constexpr ModInt operator - () const noexcept {
		return val ? mod - val : 0;
	}
	constexpr ModInt operator + (const ModInt& r) const noexcept { return ModInt(*this) += r; }
	constexpr ModInt operator - (const ModInt& r) const noexcept { return ModInt(*this) -= r; }
	constexpr ModInt operator * (const ModInt& r) const noexcept { return ModInt(*this) *= r; }
	constexpr ModInt operator / (const ModInt& r) const noexcept { return ModInt(*this) /= r; }
	constexpr ModInt& operator += (const ModInt& r) noexcept {
		val += r.val;
		if (val >= mod) val -= mod;
		return *this;
	}
	constexpr ModInt& operator -= (const ModInt& r) noexcept {
		val -= r.val;
		if (val < 0) val += mod;
		return *this;
	}
	constexpr ModInt& operator *= (const ModInt& r) noexcept {
		val = val * r.val % mod;
		return *this;
	}
	constexpr ModInt& operator /= (const ModInt& r) noexcept {
		long long a = r.val, b = mod, u = 1, v = 0;
		while (b) {
			long long t = a / b;
			a -= t * b; swap(a, b);
			u -= t * v; swap(u, v);
		}
		val = val * u % mod;
		if (val < 0) val += mod;
		return *this;
	}
	constexpr bool operator == (const ModInt& r) const noexcept {
		return this->val == r.val;
	}
	constexpr bool operator != (const ModInt& r) const noexcept {
		return this->val != r.val;
	}
	friend ostream& operator << (ostream &os, const ModInt<mod>& x) noexcept {
		return os << x.val;
	}
	friend istream& operator >> (istream &is, ModInt<mod>& x) noexcept {
		return is >> x.val;
	}
	friend constexpr ModInt<mod> modpow(const ModInt<mod> &a, long long n) noexcept {
		if (n == 0) return 1;
		auto t = modpow(a, n / 2);
		t = t * t;
		if (n & 1) t = t * a;
		return t;
	}
};