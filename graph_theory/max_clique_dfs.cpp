/*
 *  INIT: g[][]邻接矩阵
 *  CALL: res = clique(n);
 */
const int V = 10010;

int g[V][V];
int dp[V];
int stk[V][V];
int mx;

int dfs(int n, int ns, int dep)
{
    if (0 == ns)
    {
        if (dep > mx)
        {
            mx = dep;
        }
        return 1;
    }
    int i, j, k, p, cnt;
    for (i = 0; i < ns; i++)
    {
        k = stk[dep][i];
        cnt = 0;
        if (dep + n - k <= mx)
        {
            return 0;
        }
        if (dep + dp[k] <= mx)
        {
            return 0;
        }
        for (j = i + 1; j < ns; j++)
        {
            p = stk[dep][j];
            if (g[k][p])
            {
                stk[dep + 1][cnt++] = p;
            }
        }
        dfs(n, cnt, dep + 1);
    }
    return 1;
}

int clique(int n)
{
    int i, j, ns;
    for (mx = 0, i = n - 1; i >= 0; i--)    //  vertex: 0 ~ n-1
    {
        for (ns = 0, j = i + 1; j < n; j++)
        {
            if (g[i][j])
            {
                stk[1][ns++] = j;
            }
        }
        dfs(n, ns, 1);
        dp[i] = mx;
    }
    return mx;
}