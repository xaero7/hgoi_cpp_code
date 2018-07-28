const int MAXN = 1111;
int n;
double ans;
double p[MAXN];

void dfs(int x, int tot, double sum)    //  dfs(1, 0, ?)
{
    if (x == n + 1)
    {
        if (sum == 0.0)
        {
            return ;
        }

        if (tot & 1)
        {
            ans += 1 / sum; //  公式随意变
        }
        else
        {
            ans -= 1 / sum;
        }
        return ;
    }

    dfs(x + 1, tot, sum);
    dfs(x + 1, tot + 1, sum + p[x]);
}