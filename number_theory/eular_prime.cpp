/**
 * 素数筛选，查找出小于等于MAXN的素数
 * prime[0]存素数的个数，前5个素数是prime[1..5] = {2,3,5,7,11}
 * flag[i] = true表示`$i$`是素数
 */
const int MAXN = 100000;
int prime[MAXN + 1], flag[MAXN + 1];

void get_prime()
{
    for (int i = 2; i <= MAXN; i++)
    {
        if (!prime[i])
        {
            prime[++prime[0]] = i, flag[i] = true;
        }
        for (int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++)
        {
            flag[prime[j] * i] = 1;
            if (i % prime[j] == 0)
            {
                break;
            }
        }
    }
}
