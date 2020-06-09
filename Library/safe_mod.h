template<typename Integer>
Integer safe_mod(Integer a, Integer mod) {
  return ((a % mod) + mod) % mod;
}
