#require ll N
ll bit[N];
void upd(int idx, ll val){
    if(idx <= 0 or idx > N)
        return;
    while(idx < N){
        bit[idx] += val;
        idx += (idx & -idx);
    }
}
 
ll get(int idx){
    idx = max(idx, 0);
    idx = min(idx, N);
    ll sum = 0;
    while(idx > 0){
        sum += bit[idx];
        idx -= (idx & -idx);
    }
    return sum;
}