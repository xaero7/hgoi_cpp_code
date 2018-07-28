/*
 *  最小树形图
 *  int型
 *  复杂度O(NM)
 *  点从0开始
 */
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 1000010;

struct Edge
{
    int u, v, cost;
};

Edge edge[MAXM];

int pre[MAXN], id[MAXN], visit[MAXN], in[MAXN];

int zhuliu(int root, int n, int m)
{
    int res = 0, v;
    while (1)
    {
        memset(in, 0x3f, sizeof(in));

        for (int i = 0; i < m; i++)
        {
            if (edge[i].u != edge[i].v && edge[i].cost < in[edge[i].v])
            {
                pre[edge[i].v] = edge[i].u;
                in[edge[i].v] = edge[i].cost;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (i != root && in[i] == INF)
            {
                return -1;  //  不存在最小树形图
            }
        }
        int tn = 0;
        memset(id, -1, sizeof(id));
        memset(visit, -1, sizeof(visit));
        in[root] = 0;
        for (int i = 0; i < n; i++)
        {
            res += in[i];
            v = i;
            while (visit[v] != i && id[v] == -1 && v != root)
            {
                visit[v] = i;
                v = pre[v];
            }
            if (v != root && id[v] == -1)
            {
                for (int u = pre[v]; u != v ; u = pre[u])
                {
                    id[u] = tn;
                }
                id[v] = tn++;
            }
        }
        if (tn == 0)
        {
            break;  //  没有有向环
        }
        for (int i = 0; i < n; i++)
        {
            if (id[i] == -1)
            {
                id[i] = tn++;
            }
        }
        for (int i = 0; i < m; i++)
        {
            v = edge[i].v;
            edge[i].u = id[edge[i].u];
            edge[i].v = id[edge[i].v];
            if (edge[i].u != edge[i].v)
            {
                edge[i].cost -= in[v];
            }
        }
        n = tn;
        root = id[root];
    }
    return res;
}