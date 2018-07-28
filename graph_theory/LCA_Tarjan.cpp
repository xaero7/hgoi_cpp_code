/*
 *  给出一颗有向树，Q个查询
 *  输出查询结果中每个点出现次数
 *  复杂度O(n + Q);
 */
const int MAXN = 1010;
const int MAXQ = 500010;    //  查询数的最大值

//  并查集部分
int F[MAXN];                //  需要初始化为-1

int find(int x)
{
    if (F[x] == -1)
    {
        return x;
    }
    return F[x] = find(F[x]);
}

void bing(int u, int v)
{
    int t1 = find(u);
    int t2 = find(v);
    if (t1 != t2)
    {
        F[t1] = t2;
    }
}

bool vis[MAXN];             //  访问标记
int ancestor[MAXN];         //  祖先
struct Edge
{
    int to, next;
} edge[MAXN * 2];
int head[MAXN],tot;

void addedge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
}

struct Query
{
    int q, next;
    int index;              //  查询编号
} query[MAXQ * 2];

int answer[MAXQ];           //  存储最后的查询结果,下标0~Q-1
int h[MAXQ];
int tt;
int Q;

void add_query(int u, int v, int index)
{
        query[tt].q = v;
        query[tt].next = h[u];
        query[tt].index = index;
        h[u] = tt++;
        query[tt].q = u;
        query[tt].next = h[v];
        query[tt].index = index;
        h[v] = tt++;
}

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    tt = 0;
    memset(h, -1, sizeof(h));
    memset(vis, false, sizeof(vis));
    memset(F, -1, sizeof(F));
    memset(ancestor, 0, sizeof(ancestor));
}

void LCA(int u)
{
    ancestor[u] = u;
    vis[u] = true;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (vis[v])
        {
            continue;
        }
        LCA(v);
        bing(u, v);
        ancestor[find(u)] = u;
    }
    for (int i = h[u]; i != -1; i = query[i].next)
    {
        int v = query[i].q;
        if (vis[v])
        {
            answer[query[i].index] = ancestor[find(v)];
        }
    }
}

bool flag[MAXN];
int Count_num[MAXN];

int main()
{
    int n;
    int u, v, k;
    while (scanf("%d", &n) == 1)
    {
        init();
        memset(flag, false, sizeof(flag));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d:(%d)", &u, &k);
            while (k--)
            {
                scanf("%d", &v);
                flag[v] = true;
                addedge(u,v);
                addedge(v,u);
            }
        }
        scanf("%d", &Q);
        for (int i = 0; i < Q; i++)
        {
            char ch;
            cin >> ch;
            scanf("%d %d)", &u, &v);
            add_query(u, v, i);
        }
        int root;
        for (int i = 1; i <= n; i++)
        {
            if (!flag[i])
            {
                root = i;
                break;
            }
        }
        LCA(root);
        memset(Count_num, 0, sizeof(Count_num));
        for (int i = 0; i < Q; i++)
        {
            Count_num[answer[i]]++;
        }
        for (int i = 1; i <= n; i++)
        {
            if (Count_num[i] > 0)
            {
                printf("%d:%d\n", i, Count_num[i]);
            }
        }
    }
    return 0;
}