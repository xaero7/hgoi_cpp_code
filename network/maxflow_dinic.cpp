/**
 * Dinic 最大流 `$O(V^{2}E)$`
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 10000 + 10, INF = 1000000000;

struct Edge {
	int from, to, cap, flow;
};

bool operator < (const Edge& a, const Edge& b) {
	return a.from < b.from || (a.from == b.from && a.to < b.to);
}

struct Dinic
{
	int n, m, s, t;
	vector<Edge> edges;	/*边edges[i]与edges[i^1]互为反向弧*/
	vector<int> G[maxn];//G[i][j]表示结点i的第j条边在edges中的序号
	bool vis[maxn];		//BFS使用
	int d[maxn];		//d[i]表示从源点到点i的距离
	int cur[maxn];		//当前弧指针

	void init(int n)
	{
		for (int i = 0; i < n; i++) G[i].clear();
		edges.clear();
	}

	void init_flow()
	{
		for (int i = 0; i < edges.size(); i++) edges[i].flow = 0;    
	}

	void add_edges(int from, int to, int cap)
	{
		edges.push_back((Edge){from, to, cap, 0});
		edges.push_back((Edge){to, from, 0, 0});
		m = edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}

	bool BFS()
	{
		memset(vis, 0, sizeof(vis));
		queue<int> Q;
		Q.push(s);  vis[s] = 1;  d[s] = 0;
		while (!Q.empty()) {
			int x = Q.front(); Q.pop();
			for (int i = 0; i < G[x].size(); i++) {
				Edge& e = edges[G[x][i]];
				if (!vis[e.to] && e.cap > e.flow) {
					vis[e.to] = 1;
					d[e.to] = d[x] + 1;
					Q.push(e.to);
				}
			}
		}
		return vis[t];
	}

	int DFS(int x, int a)
	{
		if (x == t || a == 0) return a;
		int flow = 0, f;
		for (int& i = cur[x]; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (d[x] + 1 == d[e.to]
				&& (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
				e.flow += f;
				edges[G[x][i]^1].flow -= f;
				flow += f;
				a -= f;
				if(a == 0) break;
			}
		}
		return flow;
	}

	int max_flow(int s, int t)
	{
		this->s = s; this->t = t;
		int flow = 0;
		while (BFS()) {
			memset(cur, 0, sizeof(cur));
			flow += DFS(s, INF);
		}
		return flow;
	}
} g;

int main() {
	int n, e, s, t;
	scanf("%d%d%d%d", &n, &e, &s, &t);
	g.init(n);
	while (e--) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		g.add_edges(u, v, c);
	}
	int flow = g.max_flow(s, t);
	printf("%d\n", flow);
	return 0;
}
