// 给定两个整数，返回它们的最大公约数
int gcd(int x, int y)
{
    if (!x || !y)
    {
        return x > y ? x : y;
    }

    for (int t; t = x % y, t; x = y, y = t) ;

    return y;
}