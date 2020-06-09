template <class T>
bool ckmin(T& a, const T& b) {
  return b < a ? a = b, 1 : 0;
}