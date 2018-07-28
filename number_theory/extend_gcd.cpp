/**
 * 求x，y使得gcd(a, b) = a * x + b * y，返回gcd(a,b)的值
 */
int extgcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int d = extgcd(b, a % b, x, y);
    int t = x;
    x = y;
    y = t - a / b * y;

    return d;
}