#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int MAXN = 1000;
const int INF = 0x7f7f7f7f;

struct Node {
	int v, dist; //结点编号，以及到这个结点的距离
	Node(int u, int d) : v(u), dist(d) {}
	bool operator < (const Node& x) const {
		return dist > x.dist;
	}
};
vector<Node> G[MAXN]; //G[i]表示结点i的所有关联边
priority_queue<Node> heap;
bool vis[MAXN];
int dist[MAXN], n; //dist[i]为上一个结点到i的路径值

int prim(int v) {
	heap.push(Node(v, 0));
	int cnt = 0, ans = 0;
	while (!heap.empty() && cnt < n) {
		Node node = heap.top(); heap.pop();
		if (vis[node.v]) continue;
		vis[node.v] = true;
		ans += node.dist;
		cnt++;
		for (int i = 0; i < G[node.v].size(); i++) {
			int u = G[node.v][i].v;
			int cur_dist = G[node.v][i].dist;
			if (!vis[u] && cur_dist < dist[u]) {
				dist[u] = cur_dist;
				heap.push( Node(u, cur_dist) );
			}
		}
	}
	return ans;
}

int main() {
	int x;
	scanf("%d", &n);
	memset(dist, INF, sizeof(dist));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &x); //邻接矩阵，0表示无直接边
			if (i == j) continue;
			G[i].push_back( Node(j, x) );
		}
	}
	printf("%d\n", prim(1));
	return 0;
}