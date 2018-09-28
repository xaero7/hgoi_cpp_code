#include<bits/stdc++.h>
using namespace std;
const int maxn = 110, INF = 0x3fffffff;
struct Edge {
	int from, to, dist;
	Edge(int u, int v, int w):from(u),to(v),dist(w){}
};
struct Prim {
	int n, m;
	vector<Edge> edges;
	vector<int> G[maxn]; //G[i]表示从顶点i出发的所有边的编号 
	bool vis[maxn];
	
	void init(int n) {
		this->n = n;
		for (int i=0; i<n; i++) G[i].clear();
		edges.clear();
	}
	
	void add_edge(int from, int to, int dist) {
		edges.push_back(Edge(from, to, dist));
		m = edges.size();
		G[from].push_back(m-1);
	}
	
	int prim(int u) {
		int ans = 0;
		vis[u] = true;
		for (int i=0; i<n-1; i++) {
			int min = INF, sel_e;
			for (int j=0; j<n; j++) {
				if (!vis[j]) continue;
				for (int k=0; k<G[j].size(); k++) {
					Edge &e = edges[G[j][k]];
					if (!vis[e.to] && e.dist<min) {
						min = e.dist;
						sel_e = G[j][k];
					}
				}
			}
			Edge &e = edges[sel_e];
			vis[e.to] = true;
			ans += e.dist;
		}
		return ans;
	}
} mst;

int main() {
	int n, w;
	scanf("%d", &n);
	mst.init(n);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++) {
			scanf("%d", &w);
			if (i != j)
				mst.add_edge(i, j, w); //邻接矩阵自动会加反向边 
		}
	printf("%d\n", mst.prim(0));
}
