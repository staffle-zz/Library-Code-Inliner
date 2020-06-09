#require N
ll tin[N], tout[N];
vector<int> g[N];
ll n, timer;
void dfs(int v, int p = -1)
{
   tin[v] = ++timer;
   path[timer] = color[v];
   for (auto to : g[v])
      if (to != p)
         dfs(to, v);
   tout[v] = timer;
}