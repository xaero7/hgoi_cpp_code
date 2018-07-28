typedef long long LL;
const int MAXN = 11;
int n, m;
int a[MAXN], b[MAXN];

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++)
        {
            cin >> b[i];
        }

        LL ax = a[0], bx = b[0], x, y;
        int flag = 0;
        for (int i = 1; i < m; i++)
        {
            LL d = extgcd(ax, a[i], x, y);
            if ((b[i] - bx) % d != 0)
            {
                flag = 1;   // 无整数解
                break;
            }

            LL tmp = a[i] / d;
            x = x * (b[i] - bx) / d;    // 约分
            x = (x % tmp + tmp) % tmp;
            bx = bx + ax * x;
            ax = ax * tmp;              // ax = ax * a[i] / d
        }

        if (flag == 1 || n < bx)
        {
            puts("0");
        }
        else
        {
            LL ans = (n - bx) / ax + 1;
            if (bx == 0)
            {
                ans--;
            }
            printf("%LLd\n", ans);
        }
    }

    return 0;
}