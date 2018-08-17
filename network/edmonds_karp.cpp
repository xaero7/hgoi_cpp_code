/**
 * 实际中不用EK算法，为了理解最大流算法原理收录于此
 * 用法：
 * 先声明一个EK对象：EdmondsKarp graph;
 * 输入边，建图：graph.add_edge(u,v,c);
 * 输出最大流：graph.max_flow();
 */
struct Edge
{
	int from, to, cap, flow;
	Edge(int u, int v, int c, int f):from(u),to(v),cap(c),flow(f){}
};
struct EdmondsKarp
{
	int n, m;			//n实际结点数，最多允许结点数maxn
	vector<Edge> edges;	//边数组
	vector<int> G[maxn];//邻接表G[i][j]为点i的第j条边在edges里编号
	int a[maxn];		//源点到当前节点i的可改进量
	int p[maxn];		//最短路树上p的入弧编号
	
	void init(int n)
	{
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}
	
	void add_edge(int from, int to, int cap)
	{
		edges.push_back(Edge(from, to, cap, 0));
		edges.push_back(Edge(to, from, 0, 0));	//反向弧
		m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	
	int max_flow(int s, int t)
	{
		int flow = 0;
		for (;;) {
			memset(a, 0, sizeof(a));
			queue<int> Q;
			Q.push(s); a[s] = INF;
			while (!Q.empty() {
				int x = Q.front(); Q.pop();
				for (int i = 0; i < G[x].size(); i++) {
					Edge &e = edges[G[x][i]];
					if (!a[e.to] && e.cap > e.flow) {
						p[e.to] = G[x][i];
						a[e.to] = min(a[x], e.cap-e.flow);
						Q.push(e.to);
					}
				}
				if (a[t]) break;	//找到了一条增广路
			}
			if (!a[t]) break;		//找不到增广路了
			for (int u = t; u != s; u = edges[p[u]].from) {
				edges[p[u]].flow += a[t];	//0,1互为反向边
				edges[p[u]^1].flow -= a[t]; //2,3互为反向边；3,4; 5,6...
			}
			flow += a[t];
		}
		return flow;
	}
}