typedef long long LL;
typedef pair<int, int> pLL;

const int INF = 0x3f3f3f3f;
const int MAXN = 100000 + 10;

int n;

/*  树的重心
 *  初始化 vis[] son[] 为 0
 *  初始化 sz 为 INF
 */
int zx, sz;
int son[MAXN], vis[MAXN];
vector<pLL> edge[MAXN];

void init()
{
    for (int i = 1; i <= n; i++)
    {
        edge[i].clear();
    }
    memset(vis, 0, sizeof(vis));
    sz = INF;
    zx = -1;
}

void dfs(int r)
{
    vis[r] = 1;
    son[r] = 0;
    int tmp = 0;
    for (int i = 0; i < edge[r].size(); i++)
    {
        int v = edge[r][i].second;
        if (!vis[v])
        {
            dfs(v);
            son[r] += son[v] + 1;
            tmp = max(tmp, son[v] + 1);
        }
    }
    tmp = max(tmp, n - son[r] - 1);
    if (tmp < sz)
    {
        zx = r;
        sz = tmp;
    }
}