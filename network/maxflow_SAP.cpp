/*
 *  SAP邻接(矩阵形式_2)
 *  点的编号从0开始
 *  增加个flow数组,保留原矩阵maze,可用于多次使用最大流 
 */
const int MAXN = 1100;
int maze[MAXN][MAXN];
int gap[MAXN], dis[MAXN], pre[MAXN], cur[MAXN];
int flow[MAXN][MAXN];           //  存最大流的容量

int sap(int start, int end, int nodenum)
{
    memset(cur, 0, sizeof(cur));
    memset(dis, 0, sizeof(dis));
    memset(gap, 0, sizeof(gap));
    memset(flow, 0, sizeof(flow));
    int u = pre[start] = start, maxflow = 0, aug = -1;
    gap[0] = nodenum;
    while (dis[start] < nodenum)
    {
    loop:
        for (int v = cur[u]; v < nodenum; v++)
        {
            if (maze[u][v] - flow[u][v] && dis[u] == dis[v] + 1)
            {
                if (aug == -1 || aug > maze[u][v] - flow[u][v])
                {
                    aug = maze[u][v] - flow[u][v];
                }
                pre[v] = u;
                u = cur[u] = v;
                if (v == end)
                {
                    maxflow += aug;
                    for (u = pre[u]; v != start; v = u, u = pre[u])
                    {
                        flow[u][v] += aug;
                        flow[v][u] -= aug;
                    }
                    aug = -1;
                }
                goto loop;
            }
        }
        int mindis = nodenum - 1;
        for (int v = 0; v < nodenum; v++)
        {
            if (maze[u][v] - flow[u][v] && mindis > dis[v])
            {
                cur[u] = v;
                mindis = dis[v];
            }
        }
        if ((--gap[dis[u]]) == 0)
        {
            break;
        }
        gap[dis[u] = mindis + 1]++;
        u = pre[u];
    }
    return maxflow;
}