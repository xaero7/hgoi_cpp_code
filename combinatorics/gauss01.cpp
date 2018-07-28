/**
 * 列主元gauss消去求解a[][] * x[] = b[]
 * 返回是否有唯一解，若有解在b[]中
 */
#define fabs(x) ((x) > 0 ? (x) : (-x))
#define eps 1e-10

const int MAXN = 100;

int gauss_cpivot(int n, double a[][MAXN], double b[])
{
    int i, j, k, row = 0;
    double MAXP, temp;
    for (k = 0; k < n; k++)
    {
        for (MAXP = 0, i = k; i < n; i++)
        {
            if (fabs(a[i][k]) > fabs(MAXP))
            {
                MAXP = a[row = i][k];
            }
        }
        if (fabs(MAXP) < eps)
        {
            return 0;
        }

        if (row != k)
        {
            for (j = k; j < n; j++)
            {
                temp = a[k][j];
                a[k][j] = a[row][j];
                a[row][j] = temp;
                temp = b[k];
                b[k] = b[row];
                b[row] = temp;
            }
        }
        for (j = k + 1; j < n; j++)
        {
            a[k][j] /= MAXP;
            for (i = k + 1; i < n; i++)
            {
                a[i][j] -= a[i][k] * a[k][j];
            }
        }
        b[k] /= MAXP;
        for (i = n - 1; i >= 0; i--)
        {
            for (j = i + 1; j < n; j++)
            {
                b[i] -= a[i][j] * b[j];
            }
        }
    }

    return 1;
}