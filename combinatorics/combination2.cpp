typedef long long LL;
const LL MOD = 1e9 + 7;     //  必须为质数才管用
const LL MAXN = 1e5 + 3;
LL fac[MAXN];       //  阶乘
LL inv[MAXN];       //  阶乘的逆元

LL QPow(LL x, LL n)
{
    LL ret = 1;
    LL tmp = x % MOD;

    while (n)
    {
        if (n & 1)
        {
            ret = (ret * tmp) % MOD;
        }
        tmp = tmp * tmp % MOD;
        n >>= 1;
    }

    return ret;
}

void init()
{
    fac[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inv[MAXN - 1] = QPow(fac[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; i--)
    {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

LL C(LL a, LL b)
{
    if (b > a)
    {
        return 0;
    }
    if (b == 0)
    {
        return 1;
    }
    return fac[a] * inv[b] % MOD * inv[a - b] % MOD;
}