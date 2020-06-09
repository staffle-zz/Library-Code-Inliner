#require M
string s[M];
bool vis[M][M];
int n, m;
 		// 	U  R    D  L cloclwise moves
int dr[] = {+1, 0, -1, 0};
int dc[] = {0, +1, 0, -1};
bool isvalid(int nr,int nc){
    return nr>=0 and nr<n and nc>=0 and nc<m;
}
void dfs(int r, int c)
{
    vis[r][c] = true;
    for(int d = 0; d < 4; d++){
        int nr = r+dr[d];
        int nc = c+dc[d];
        if(isvalid(nr,nc) and s[nr][nc]=='#' and !vis[nr][nc]){
            dfs(nr, nc);
        }
    }
}