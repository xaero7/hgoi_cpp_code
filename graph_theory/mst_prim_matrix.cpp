#include<cstdio>
#include<cstring>

const int MAXN = 1000;
const int INF = 0x7f7f7f7f;
int G[MAXN][MAXN];
int dist[MAXN], vis[MAXN], n;

int prim(int v) {
	for (int i = 1; i <= n; i++) dist[i] = G[v][i];
	vis[v] = 1;
	int ans = 0;
	for (int i = 1; i < n; i++) {
		int min = INF, k = 0;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && dist[j] < min) {
				min = dist[j];
				k = j;
			}
		}
		if (k == 0) return -1; //原图是非连通图
		vis[k] = 1, ans += min;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && G[k][j] < dist[j])
				dist[j] = G[k][j];
		}
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	//memset(G, INF, sizeof(G));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &G[i][j]); //邻接矩阵，0表示无直接边
			if (G[i][j] == 0) G[i][j] = INF;
		}
	}
	printf("%d\n", prim(1));
	for (int i=0; i<=n; i++)
		printf("%d\n", dist[i]);
	return 0;
}