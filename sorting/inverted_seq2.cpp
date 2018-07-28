/**
 * DP：f(n,m)表示逆序数为m的n元排列的个数，则
 * `$f(n+1,m) = f(n,m)+f(n,m-1)+ \cdots + f(n,m-n)$`
 * 当 b<0 时, f(a,b) = 0
 * 优化又考虑到如果直接利用上式计算时间复杂度为`$O(n^3)$`,我们分析上 
 * 式不难发现f(n + 1, m) = f(n, m) + f(n + 1, m - 1)
 * end = node[index].e,
 * if(m-n-1 >= 0) f(n+1, m) -= f(n, m-n-1).
 */
const int N = 1001;
const int C = 10001;
const long MOD = 1000000007;
long arr[N][C];
long long temp;

int main()
{
    int i, j;
    arr[1][0] = arr[2][0] = arr[2][1] = 1;
    for (i = 3; i < N; ++i)
    {
        arr[i][0] = 1;
        long h = i * (i + 1) / 2 + 1;
        if (h > C)
        {
            h = C;
        }
        for (j = 1; j < h; ++j)
        {
            temp = arr[i - 1][j] + arr[i][j - 1];
            arr[i][j] = temp % MOD;
            if (j - i >= 0)
            {
                arr[i][j] -= arr[i - 1][j - i];
                if (arr[i][j] < 0)
                {   //  注意:由于arr[i][j]和arr[i - 1][j - i]都是模过的,所以可能会得到负数
                    arr[i][j] += MOD;
                }
            }
        }
    }
    while (scanf("%d %d", &i, &j) != EOF)
    {
        printf("%ld\n", arr[i][j]);
    }
    return 0;
}