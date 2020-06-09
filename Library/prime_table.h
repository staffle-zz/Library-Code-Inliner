template<typename Table>
Table prime_table(size_t size) {
  Table table(size, true);
  table[0] = table[1] = false;
  for(size_t div = 2;div * div <= size;div++) {
    if(table[div]) {
      for(size_t mult = div * div;mult < size;mult += div) {
	        table[mult] = false;
      }
    }
  }
  return table;
}
