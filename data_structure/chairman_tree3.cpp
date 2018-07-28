/*
 *  LCA + 主席树
 */
//  主席树部分
const int MAXN = 200010;
const int M = MAXN * 40;
int n, q, m, TOT;
int a[MAXN], t[MAXN];
int T[MAXN], lson[M], rson[M], c[M];
void Init_hash()
{
    for (int i = 1; i <= n; i++)
    {
        t[i] = a[i];
    }
    sort(t + 1, t + 1 + n);
    m = (int)(unique(t + 1, t + n + 1) - t - 1);
    return ;
}

int build(int l, int r)
{
    int root = TOT++;
    c[root] = 0;
    if (l != r)
    {
        int mid = (l + r) >> 1;
        lson[root] = build(l, mid);
        rson[root] = build(mid + 1, r);
    }
    return root;
}

int hash_(int x)
{
    return (int)(lower_bound(t + 1, t + 1 + m, x) - t);
}

int update(int root, int pos, int val)
{
    int newroot = TOT++, tmp = newroot;
    c[newroot] = c[root] + val;
    int l = 1, r = m;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        if (pos <= mid)
        {
            lson[newroot] = TOT++;
            rson[newroot] = rson[root];
            newroot = lson[newroot];
            root = lson[root];
            r = mid;
        }
        else
        {
            rson[newroot] = TOT++;
            lson[newroot] = lson[root];
            newroot = rson[newroot];
            root = rson[root];
            l = mid + 1;
        }
        c[newroot] = c[root] + val;
    }
    return tmp;
}

int query(int left_root, int right_root, int LCA, int k)
{
    int lca_root = T[LCA];
    int pos = hash_(a[LCA]);
    int l = 1, r = m;
    while (l < r)
    {
        int mid = (l + r) >> 1;
        int tmp = c[lson[left_root]] + c[lson[right_root]] - 2 * c[lson[lca_root]] + (pos >= l && pos <= mid);
        if (tmp >= k)
        {
            left_root = lson[left_root];
            right_root = lson[right_root];
            lca_root = lson[lca_root];
            r = mid;
        }
        else
        {
            k -= tmp;
            left_root = rson[left_root];
            right_root = rson[right_root];
            lca_root = rson[lca_root];
            l = mid + 1;
        }
    }
    return l;
}

//  LCA部分
int rmq[2 * MAXN];  //  rmq数组,就是欧拉序列对应的深度序列

struct ST
{
    int mm[2 * MAXN];
    int dp[2 * MAXN][20];   //  最小值对应的下标
    void init(int n)
    {
        mm[0] = -1;
        for (int i = 1; i <= n; i++)
        {
            mm[i] = ((i & (i - 1)) == 0) ? mm[i - 1] + 1 : mm[i - 1];
            dp[i][0] = i;
        }
        for (int j = 1; j <= mm[n]; j++)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                dp[i][j] = rmq[dp[i][j - 1]] < rmq[dp[i + (1 << (j - 1))][j - 1]] ? dp[i][j - 1] : dp[i + (1 << (j - 1))][j - 1];
            }
        }
        return ;
    }
    int query(int a, int b) //  查询[a,b]之间最小值的下标
    {
        if (a > b)
        {
            swap(a, b);
        }
        int k = mm[b - a + 1];
        return rmq[dp[a][k]] <= rmq[dp[b - (1 << k) + 1][k]] ? dp[a][k] : dp[b - (1 << k) + 1][k];
    }
};

//  边的结构体定义
struct Edge
{
    int to, next;
};

Edge edge[MAXN * 2];
int tot, head[MAXN];
int F[MAXN * 2];    //  欧拉序列,就是dfs遍历的顺序,长度为2*n-1,下标从1开始
int P[MAXN];        //  P[i]表示点i在F中第一次出现的位置
int cnt;
ST st;

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    return ;
}

void addedge(int u, int v)  //  加边,无向边需要加两次
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
    return ;
}

void dfs(int u, int pre, int dep)
{
    F[++cnt] = u;
    rmq[cnt] = dep;
    P[u] = cnt;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == pre)
        {
            continue;
        }
        dfs(v, u, dep + 1);
        F[++cnt] = u;
        rmq[cnt] = dep;
    }
    return ;
}

void LCA_init(int root, int node_num)   //  查询LCA前的初始化
{
    cnt = 0;
    dfs(root, root, 0);
    st.init(2 * node_num - 1);
    return ;
}

int query_lca(int u, int v)              //  查询u,v的lca编号
{
    return F[st.query(P[u], P[v])];
}

void dfs_build(int u, int pre)
{
    int pos = hash_(a[u]);
    T[u] = update(T[pre], pos, 1);
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == pre)
        {
            continue;
        }
        dfs_build(v, u);
    }
    return ;
}


int main()
{
    //  freopen("in.txt", "r", stdin);
    //  freopen("out.txt", "w", stdout);
    while (scanf("%d%d", &n, &q) == 2)
    {
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        Init_hash();
        init();
        TOT = 0;
        int u, v;
        for (int i = 1; i < n; i++)
        {
            scanf("%d%d", &u, &v);
            addedge(u, v);
            addedge(v, u);
        }
        LCA_init(1, n);
        T[n + 1] = build(1, m);
        dfs_build(1, n + 1);
        int k;
        while (q--)
        {
            scanf("%d%d%d", &u, &v, &k);
            printf("%d\n", t[query(T[u], T[v], query_lca(u, v), k)]);
        }
    }
    return 0;
}