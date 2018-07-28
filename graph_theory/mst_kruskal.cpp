#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 1000;

struct Edge {
	int from, to, dist; //两个端点及距离
	Edge(int u, int v, int d) : from(u), to(v), dist(d) {}
	bool operator < (const Edge& x) const {
		return dist < x.dist;
	}
};
vector<Edge> edges;
int father[MAXN], rank1[MAXN]; //rank会和Linux系统名冲突
int n;

int find(int x) {
	if (x == father[x]) {
		return x;
	} else {
		return father[x] = find(father[x]);
	}
}

void merge(int x, int y) {
	if (rank1[x] < rank1[y]) {
		father[x] = father[y];
	} else {
		father[y] = father[x];
		if (rank1[x] == rank1[y])
			rank1[x]++;
	}
}

int kruskal() {
	memset(rank1, 0, sizeof(rank1));
	for (int i = 1; i <= n; i++) father[i] = i;
	int ans = 0;
	for (int i = 0; i < edges.size(); i++) {
		Edge &e = edges[i];
		int u = find(e.from);
		int v = find(e.to);
		if (u != v) {
			ans += e.dist;
			merge(u, v);
		}
	}
	return ans;
}

int main() {
	int x;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &x); //邻接矩阵，0表示无直接边
			if (i < j) {
				edges.push_back( Edge(i, j, x) );
			}
		}
	}
	sort(edges.begin(), edges.end());
	printf("%d\n", kruskal());
	return 0;
}