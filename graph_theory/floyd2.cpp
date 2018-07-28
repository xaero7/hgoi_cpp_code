/*
 *  Floyd算法，求从任意节点i到任意节点j的最短路径
 *  cost[][]:初始化为INF（cost[i][i]：初始化为0）
 *  val[]:点权，lowcost[][]:除起点、终点外的点权之和+最短路径
 *  path[][]:路径限制，要求字典序最小的路径，下标1~N
 */
const int MAXN = 110;
const int INF = 0x1f1f1f1f;

int val[MAXN];          //  点权
int cost[MAXN][MAXN];
int lowcost[MAXN][MAXN];
int path[MAXN][MAXN];   //  i~j路径中的第一个结点

void Floyd(int n)
{
    memcpy(lowcost, cost, sizeof(cost));
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            path[i][j] = j;
        }
    }

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int temp = lowcost[i][k] + lowcost[k][j] + val[k];
                if (lowcost[i][j] > temp)
                {
                    lowcost[i][j] = temp;
                    path[i][j] = path[i][k];
                }
                else if (lowcost[i][j] == temp && path[i][j] > path[i][k])
                {
                    path[i][j] = path[i][k];
                }
            }
        }
    }
    return ;
}