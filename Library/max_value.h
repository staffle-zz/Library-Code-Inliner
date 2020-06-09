#require ckmax
template<typename Container>
typename Container::value_type max_value(const Container &container) {
  typename Container::value_type maxi = *container.begin();
  for(auto elem : container) {
    ckmax(maxi,elem);
  }
  return maxi;
}
