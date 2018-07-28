/*
 *  单源最短路径，dijkstra算法，邻接矩阵形式，复杂度为O(n^2)
 *  两点间距离存入map[][],两点间花费存入cost[][]
 *  求出源st到所有点的最短路径及其对应最小花费
 *  返回各点的最短路径lowdis[]以及对应的最小花费lowval[]
 *  可更改路径权类型，但是权值必须为非负，下标1~n
 */

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

int n, m;

int lowdis[MAXN];
int lowval[MAXN];
int visit[MAXN];
int map[MAXN][MAXN];
int cost[MAXN][MAXN];

void dijkstra(int st)
{
    int temp = 0;
    for (int i = 1; i <= n; i++)
    {
        lowdis[i] = map[st][i];
        lowval[i] = cost[st][i];
    }
    memset(visit, 0, sizeof(visit));

    visit[st] = 1;
    for (int i = 1; i < n; i++)
    {
        int MIN = INF;
        for (int j = 1; j <= n; j++)
        {
            if (!visit[j] && lowdis[j] < MIN)
            {
                temp = j;
                MIN = lowdis[j];
            }
        }
        visit[temp] = 1;
        for (int j = 1; j <= n; j++)
        {
            if (!visit[j] && map[temp][j] < INF)
            {
                if (lowdis[j] > lowdis[temp] + map[temp][j])
                {
                    lowdis[j] = lowdis[temp] + map[temp][j];
                    lowval[j] = lowval[temp] + cost[temp][j];
                }
                else if (lowdis[j] == lowdis[temp] + map[temp][j])
                {
                    if (lowval[j] > lowval[temp] + cost[temp][j])
                    {
                        lowval[j] = lowval[temp] + cost[temp][j];
                    }
                }
            }
        }
    }

    return ;
}