/*
 *  INIT: g[][]置为邻接矩阵; 
 *  CALL: cardinality(n);tag[i]为排列中第i个点的标号;
 */
const int V = 10010;
int tag[V], g[V][V], deg[V], vis[V];

void cardinality(int n)
{
    int i, j, k;
    memset(deg, 0, sizeof(deg));
    memset(vis, 0, sizeof(vis));
    for (i = n - 1; i >= 0; i--)
    {
        for (j = 0, k = -1; j < n; j++)
        {
            if (0 == vis[j])
            {
                if (k == -1 || deg[j] > deg[k])
                {
                    k = j;
                }
            }
        }
        vis[k] = 1, tag[i] = k;
        for (j = 0; j<n; j++)
        {
            if (0 == vis[j] && g[k][j])
            {
                deg[j]++;
            }
        }
    }
    return ;
}