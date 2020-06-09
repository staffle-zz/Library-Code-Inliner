
namespace IO {
template <class T>
void re(complex<T>& x);
template <class T1, class T2>
void re(pair<T1, T2>& p);
inline bool blank(char c) {
  return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
};
template <class T>
void re(vector<T>& a);
template <class T, size_t SZ>
void re(array<T, SZ>& a);
void re(int& x) { scanf("%d", &x); }
void re(long& x) { scanf("%ld", &x); }
void re(long long& x) { scanf("%lld", &x); }
void re(unsigned& x) { scanf("%u", &x); }
void re(unsigned long& x) { scanf("%lu", &x); }
void re(unsigned long long& x) { scanf("%llu", &x); }
void re(float& x) { scanf("%f", &x); }
void re(double& x) { scanf("%lf", &x); }
void re(long double& x) { scanf("%Lf", &x); }
bool red(char& x) {
  if (scanf("%c", &x) == EOF) return false;
  if (blank(x)) return red(x);
  return true;
}
bool re(char& x) {
  if (scanf("%c", &x) == EOF) return false;
  return true;
}
void re(string& x) {
  char c;
  x = "";
  if (!red(c)) return;
  while (!blank(c)) {
    x.push_back(c);
    if (!re(c)) break;
  }
}
template <class T, class... Ts>
void re(T& t, Ts&... ts) {
  re(t);
  re(ts...);
}
template <class T>
void re(complex<T>& x) {
  T a, b;
  re(a, b);
  x = {a, b};
}
template <class T1, class T2>
void re(pair<T1, T2>& p) {
  re(p.first, p.second);
};
template <class T>
void re(vector<T>& a) {
  for (int i = 0; i < (int)a.size(); i++) re(a[i]);
}
template <class T, size_t SZ>
void re(array<T, SZ>& a) {
  for (int i = 0; i < SZ; i++) re(a[i]);
}
void pr(int x) { printf("%d", x); }
void pr(long x) { printf("%ld", x); }
void pr(long long x) { printf("%lld", x); }
void pr(unsigned x) { printf("%u", x); }
void pr(unsigned long x) { printf("%lu", x); }
void pr(unsigned long long x) { printf("%llu", x); }
void pr(float x) { printf("%.3f", x); }
void pr(double x) { printf("%.6lf", x); }
void pr(long double x) { printf("%.10Lf", x); }
void pr(char x) { printf("%c", x); }
void pr(const char* x) { printf("%s", x); }
void pr(const string& x) { printf("%s", x.c_str()); }
void pr(bool x) { pr(x ? "true" : "false"); }
template <class T>
void pr(const complex<T>& x) {
  cout << x;
}
template <class T1, class T2>
void pr(const pair<T1, T2>& x);
template <class T, class... Ts>
void pr(const T& t, const Ts&... ts) {
  pr(t);
  pr(ts...);
}
template <class T1, class T2>
void pr(const pair<T1, T2>& x) {
  pr("(", x.ff, ", ", x.ss, ")");
}
template <class T>
void pr(const T& x) {
  pr("{");
  bool fst = 1;
  for (const auto& a : x) pr(!fst ? ", " : "", a), fst = 0;
  pr("}");
}
void pl() { pr("\n"); }
template <class T, class... Ts>
void pl(const T& t, const Ts&... ts) {
  pr(t);
  if (sizeof...(ts)) pr(" ");
  pl(ts...);
}
};
using namespace IO;

#main


