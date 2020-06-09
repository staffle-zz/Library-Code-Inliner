#require digits reversed

template<typename Container>
bool is_palindromic_sequence(const Container &a) {
  return a == reversed(a);
}

template<typename Type>
bool is_palindromic_number(const Type &a) {
  return is_palindromic_sequence<vector<Type>>(digits<vector<Type>>(a));
}
