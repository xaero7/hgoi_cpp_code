/*
 *  二分套二分
 *  数组A同数组B组合乘积，二分查找第K大
 */
typedef long long LL;

const int MAXN = 5e4 + 10;

LL N, K;

LL A[MAXN];
LL B[MAXN];

//  查找小于x的元素个数
LL check(LL x)
{
    LL j = N, ans = 0;
    for (int i = 1; i <= N; i++)
    {
        for (; j > 0;)
        {
            if (A[i] * B[j] > x)
            {
                j--;
            }
            else
            {
                break;
            }
        }
        ans += j;
    }
    return ans;
}

int main(int argc, const char * argv[])
{
    cin >> N >> K;

    for (int i = 1; i <= N; i++)
    {
        scanf("%LLd %LLd", A + i, B + i);
    }
    sort(A + 1, A + N + 1);
    sort(B + 1, B + N + 1);

    LL ans = 0;
    LL key = N * N - K + 1;
    LL low = A[1] * B[1];   //  初始最小值
    LL high = A[N] * A[N];  //  初始最大值

    while (high - low > 1)
    {
        LL mid = (low + high) >> 1;
        if (check(mid) >= key)
        {
            ans = mid;
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    cout << ans << '\n';
    return 0;
}