const int maxn = 100010;
int n, m;
vector<int> G[maxn];
int low[maxn], pre[maxn];
int dfs_clock = 0;						//时间戳
int iscut[maxn], cnt_cut = 0;			//标记是否为割顶
int bridges = 0;

int dfs(int u, int fa)					//u在DFS树中的父结点是fa 
{
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0; i < G[u].size(); i++)
    {
        int v = G[u][i];
        if(0 == pre[v])					//没有访问的v
        {
            child++;					//孩子节点的数目
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);		//用后代更新u的low函数 
            if (lowv >= pre[u])
				iscut[u] = 1;			//割顶的个数 
            if (lowv > pre[u])
				bridges++;				//桥边的条数 
        }
        else if (pre[v] < pre[u] && v != fa)
        {
            lowu = min(lowu,pre[v]);	//用反向边更新u的low函数 
        }
    }
    if (fa < 0 && child == 1)
		iscut[u] = 0;					//对于根结点的处理
    low[u] = lowu;
    return lowu;
}


int main()
{
    while(scanf("%d%d",&n,&m)!=EOF && n)
    {
        memset(pre, 0, sizeof(pre));
        memset(iscut, 0, sizeof(iscut));
        cnt_cut = bridges = dfs_clock = 0;
        for(int i = 0; i <= n; i++) G[i].clear();
        int u, v;
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for (int i = 1; i <= n; i++) if (!pre[i]) dfs(i, -1);
        for (int i = 1; i <= n; i++) if (iscut[i]) cnt_cut++;
        printf("%d %d\n", cnt_cut, bridges);
        for(int i = 1; i <= n; i++) if (iscut[i]) printf("%d\n", i);
    }
    return 0;
}
