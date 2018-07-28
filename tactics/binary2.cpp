/*
 *  传入参数必须在a[l]与a[h]之间
 *  假设a数组已经按从小到大排序
 *  返回值l总是合理的
 */
int bs(int a[], int l, int h, int v)
{
    int m;
    while (l < h)
    {
        m = (l + h) >> 1;
        if (a[m] < v)
        {
            l = m + 1;
        }
        else
        {
            h = m;
        }
    }
    return l;
}