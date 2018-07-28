int father[MAXN]; //祖先数组
int rank[MAXN]; //秩，树高

void make_set(int x)
{
    father[x] = x;
    rank[x] = 0;
} 

int find_set(int x)
{
    if (x != father[x])
        father[x] = find_set(father[x])
    return father[x];
}

void union_set(int x, y)
{
	x = find_set(x);
	y = find_set(y);
	if (x==y) return;
	if (rank[x]<rank[y])
		father[x] = father[y];
	else
	{
		father[y] = father[x];
		if (rank[x] == rank[y])
			rank[x]++;
	}
}
