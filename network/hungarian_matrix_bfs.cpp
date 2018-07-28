/*
 *  INIT: g[][]邻接矩阵;
 *  CALL: res = MaxMatch();Nx, Ny初始化!!! 
 *  优点:适用于稀疏二分图,边较少,增广路较短。
 *  匈牙利算法的理论复杂度是O(VE)
 */
const int MAXN = 1000;
int g[MAXN][MAXN], Mx[MAXN], My[MAXN], Nx, Ny;
int chk[MAXN], Q[MAXN], prev[MAXN];

int MaxMatch()
{
    int res = 0;
    int qs, qe;
    memset(Mx, -1, sizeof(Mx));
    memset(My, -1, sizeof(My));
    memset(chk, -1, sizeof(chk));
    for (int i = 0; i < Nx; i++)
    {
        if (Mx[i] == -1)
        {
            qs = qe = 0;
            Q[qe++] = i;
            prev[i] = -1;
            bool flag = 0;
            while (qs < qe && !flag)
            {
                int u = Q[qs];
                for (int v = 0; v < Ny && !flag; v++)
                {
                    if (g[u][v] && chk[v] != i)
                    {
                        chk[v] = i; Q[qe++] = My[v];
                        if (My[v] >= 0)
                        {
                            prev[My[v]] = u;
                        }
                        else
                        {
                            flag = 1;
                            int d = u, e = v;
                            while (d != -1)
                            {
                                int t = Mx[d];
                                Mx[d] = e;
                                My[e] = d;
                                d = prev[d];
                                e = t;
                            }
                        }
                    }
                }
                qs++;
            }
            if (Mx[i] != -1)
            {
                res++;
            }
        }
    }
    return res;
}