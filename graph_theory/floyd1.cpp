/*
 *  Floyd算法，求从任意节点i到任意节点j的最短路径
 *  cost[][]:初始化为INF（cost[i][i]：初始化为0）
 *  lowcost[][]:最短路径，path[][]:最短路径（无限制）
 */
const int MAXN = 100;

int cost[MAXN][MAXN];
int lowcost[MAXN][MAXN];
int path[MAXN][MAXN];

void Floyd(int n)
{
    memcpy(lowcost, cost, sizeof(cost));
    memset(path, -1, sizeof(path));

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (lowcost[i][j] > (lowcost[i][k] + lowcost[k][j]))
                {
                    lowcost[i][j] = lowcost[i][k] + lowcost[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    return ;
}