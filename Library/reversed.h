template<typename Container>
Container reversed(Container container) {
  reverse(container.begin(), container.end());
  return container;
}
