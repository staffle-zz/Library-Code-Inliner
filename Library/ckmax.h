template <class T>
bool ckmax(T& a, const T& b) {
  return a < b ? a = b, 1 : 0;
}