template<typename Container>
Container subarray(const Container &a, size_t begin, size_t end) {
  Container res;
  for(size_t i = begin;i < end;i++) {
    inserter(res, res.end()) = a[i];
  }
  return res;
}
