/**
 * 方程`$ax \equiv b \pmod{n}$`的`$x$`解
 */
void modeq(int a, int b, int n)
{
    int e, i, d, x, y;
    d = extgcd(b, a % b, x, y);
    if (b % d > 0)
    {
        cout << "No answer!\n";
    }
    else
    {
        e = (x * (b / d)) % n;
        for (i = 0; i < d; i++)
        {
            cout << i + 1 << "-th ans:" << (e + i * (n / d)) % n << '\n';
        }
    }
    return ;
}