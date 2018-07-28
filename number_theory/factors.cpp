/**
 * 合数的分解需要先进行素数的筛选
 * factor[i][0]存放分解的素数
 * factor[i][1]存放对应素数出现的次数
 * fatCnt存放合数分解出的素数个数(相同的素数只算一次)
 */
long long factor[100][2];
int fatCnt;

int get_factors(long long x)
{
    fatCnt = 0;
    long long tmp = x;
    for (int i = 1; prime[i] <= tmp / prime[i]; i++)
    {
        factor[fatCnt][1] = 0;
        if (tmp % prime[i] == 0)
        {
            factor[fatCnt][0] = prime[i];
            while (tmp % prime[i] == 0)
            {
                factor[fatCnt][1]++;
                tmp /= prime[i];
            }
            fatCnt++;
        }
    }
    if (tmp != 1)
    {
        factor[fatCnt][0] = tmp;
        factor[fatCnt++][1] = 1;
    }
    return fatCnt;
}