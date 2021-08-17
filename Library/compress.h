template <typename T> vector<pair<T, int>> compress(vector<T> dt) {
    vector<pair<T, int>> ans;
    if (dt.size() == 0)
        return ans;
    pair<T, int> cur = {dt[0], 1};
    int n = dt.size();

    for (int i = 1; i < n; ++i) {
        if (dt[i] == cur.first)
            cur.second++;
        else {
            ans.push_back(cur);
            cur = {dt[i], 1};
        }
    }
    ans.push_back(cur);

    return ans;
}
vector<pair<char, int>> compress(string s) {
    int n = s.length();
    vector<char> dt(n);
    for (int i = 0; i < n; ++i)
        dt[i] = s[i];
    return compress(dt);
}