template<typename Container, typename SumType = long long>
class prefix_sum_table {
private:
  vector<SumType> table;
public:
  template<typename Container, typename SumType>
  prefix_sum_table(const Container &a) {
    SumType prefix_sum = 0;
    inserter(table, table.end()) = prefix_sum;

    for(auto elem : a) {
      prefix_sum = prefix_sum + elem;
      inserter(table, table.end()) = prefix_sum;
    }
  }
  prefix_sum_table(){};
  SumType sum_between(size_t begin, size_t end) {
    return table[end] - table[begin];
  }
};
