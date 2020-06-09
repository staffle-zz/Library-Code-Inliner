#require macro N
ll ans[N], a[N]; // check limits for N
namespace sqrtDecomp{
    const int block = sqrt(N) + 1;
    struct Mo{
       int l, r, id;
       Mo (int l, int r, int id) : l(l), r(r), id(id) {}
       bool operator <(const Mo &N)const{
          return l / block == N.l / block ? r < N.r : l / block < N.l / block;
       }
    };
    int l = 1,r = 0;
    ll now_answer = 0;
    void add(int x){  
        ans += a[x];
    }
     
    void del(int x)
    {
        ans -= a[x];
    }
    void processquery(Mo cur){
        while (l > cur.l)
            add(--l);
        while (r < cur.r)
            add(++r);
        while (r > cur.r)
            del(r--);
        while (l < cur.l)
            del(l++);
        ans[cur.id] = now_answer;
    };
    void Algo(){
        vector<Mo> queries(q); // check this
        for (int i = 0; i < q; ++i){
            cin >> x >> y;
            queries[i] = Mo(x,y,i);
        }
        sort(queries.begin(), queries.end());
        for(auto query:queries){
            processquery(query);
        }
        for (int i = 0; i < q; ++i){
            cout << ans[i] << "\n";        
        }
    }
 
};
using namespace sqrtDecomp;