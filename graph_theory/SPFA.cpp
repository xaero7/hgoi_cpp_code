/*
 *  时间复杂度O(kE)
 *  队列实现，有时候改成栈实现会更快，较容易修改
 */

const int MAXN = 1010;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int v, cost;
    Edge(int _v = 0, int _cost = 0) : v(_v), cost(_cost) {}
};
vector<Edge> E[MAXN];

void addEdge(int u, int v, int w)
{
    E[u].push_back(Edge(v, w));
}

bool vis[MAXN]; // 在队列标志
int cnt[MAXN];  // 每个点的入列队次数
int dist[MAXN]; // dist[i]表示起点start到i的最短路值

bool SPFA(int start, int n)
{
    memset(vis, false, sizeof(vis));
    memset(dist, 0x3f, sizeof(dist));
    memset(cnt, 0, sizeof(cnt));

    vis[start] = true;
    dist[start] = 0;
    queue<int> que;
    while (!que.empty()) que.pop();
    
    que.push(start), cnt[start] = 1;
    while (!que.empty())
    {
        int u = que.front(); que.pop();
        vis[u] = false;

        for (int i = 0; i < E[u].size(); i++)
        {
            int v = E[u][i].v;
            if (dist[v] > dist[u] + E[u][i].cost)
            {
                dist[v] = dist[u] + E[u][i].cost;
                if (!vis[v])
                {
                    vis[v] = true;
                    que.push(v);
                    if (++cnt[v] > n)
                    {
                        return false;   // cnt[i]为入队列次数，用来判定是否存在负环回路
                    }
                }
            }
        }
    }

    return true;
}