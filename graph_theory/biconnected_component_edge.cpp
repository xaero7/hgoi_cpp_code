/*
 *  POJ 2942 Knights of the Round Table 
 *  亚瑟王要在圆桌上召开骑士会议,为了不引发骑士之间的冲突, 
 *  并且能够让会议的议题有令人满意的结果,每次开会前都必须对出席会议的骑士有如下要求: 
 *  1、 相互憎恨的两个骑士不能坐在直接相邻的2个位置;
 *  2、 出席会议的骑士数必须是奇数,这是为了让投票表决议题时都能有结果。
 *  注意:1、所给出的憎恨关系一定是双向的,不存在单向憎恨关系。
 *  2、由于是圆桌会议,则每个出席的骑士身边必定刚好有2个骑士。
 *  即每个骑士的座位两边都必定各有一个骑士。
 *  3、一个骑士无法开会,就是说至少有3个骑士才可能开会。
 *  首先根据给出的互相憎恨的图中得到补图。
 *  然后就相当于找出不能形成奇圈的点。
 *  利用下面两个定理: 
 *  (1)如果一个双连通分量内的某些顶点在一个奇圈中(即双连通分量含有奇圈), 那么这个双连通分量的其他顶点也在某个奇圈中; 
 *  (2)如果一个双连通分量含有奇圈,则他必定不是一个二分图。反过来也成立,这是一个充要条件。
 *  所以本题的做法,就是对补图求点双连通分量。然后对于求得的点双连通分量,使用染色法判断是不是二分图,不是二分图,这个双连通分量的点是可以存在的
 */
const int MAXN = 1010;
const int MAXM = 2000010;

struct Edge
{
    int to, next;
} edge[MAXM];
int head[MAXN], tot;
int Low[MAXN], DFN[MAXN], Stack[MAXN], Belong[MAXN];
int Index,top;
int block;      //  点双连通分量的个数
bool Instack[MAXN];
bool can[MAXN];
bool ok[MAXN];  //  标记
int tmp[MAXN];  //  暂时存储双连通分量中的点
int cc;         //  tmp的计数
int color[MAXN];//  染色

void addedge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].next = head[u];
    head[u] = tot++;
    return ;
}

bool dfs(int u, int col)    //  染色判断二分图
{
    color[u] = col;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (!ok[v])
        {
            continue;
        }
        if (color[v] != -1)
        {
            if (color[v]==col)
            {
                return false;
            }
            continue;
        }
        if (!dfs(v,!col))
        {
            return false;
        }
    }
    return true;
}

void Tarjan(int u, int pre)
{
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        v = edge[i].to;
        if (v == pre)
        {
            continue;
        }
        if (!DFN[v])
        {
            Tarjan(v, u);
            if (Low[u] > Low[v])
            {
                Low[u] = Low[v];
            }
            if (Low[v] >= DFN[u])
            {
                block++;
                int vn;
                cc = 0;
                memset(ok, false, sizeof(ok));
                do
                {
                    vn = Stack[--top];
                    Belong[vn] = block;
                    Instack[vn] = false;
                    ok[vn] = true;
                    tmp[cc++] = vn;
                }
                while (vn!=v);
                ok[u] = 1;
                memset(color, -1, sizeof(color));
                if (!dfs(u,0))
                {
                    can[u] = true;
                    while (cc--)
                    {
                        can[tmp[cc]] = true;
                    }
                }
            }
        }
        else if (Instack[v] && Low[u] > DFN[v])
        {
            Low[u] = DFN[v];
        }
    }
}

void solve(int n)
{
    memset(DFN, 0, sizeof(DFN));
    memset(Instack, false, sizeof(Instack));
    Index = block = top = 0;
    memset(can, false, sizeof(can));
    for (int i = 1; i <= n; i++)
    {
        if (!DFN[i])
        {
            Tarjan(i, -1);
        }
    }
    int ans = n;
    for (int i = 1; i <= n; i++)
    {
        if(can[i])
        {
            ans--;
        }
    }
    printf("%d\n", ans);
}

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
}

int g[MAXN][MAXN];

int main()
{
    int n, m;
    int u, v;
    while (scanf("%d%d", &n, &m) == 2)
    {
        if (n == 0 && m == 0)
        {
            break;
        }
        init();
        memset(g, 0, sizeof(g));
        while (m--)
        {
            scanf("%d%d", &u, &v);
            g[u][v] = g[v][u] = 1;
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if(i != j && g[i][j] == 0)
                {
                    addedge(i, j);
                }
            }
        }
        solve(n);
    }
    return 0;
}