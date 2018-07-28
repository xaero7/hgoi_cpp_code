/*
 *  在下标[l, r]范围内查找,返回下标
 *  假设a数组已经按从小到大排序
 *  失败返回-1
 */
int bs(int a[], int l, int r, int v)
{
    int m;
    while (l < r)
    {
        m = (l + r + 1) >> 1;
        if (a[m] > v)
        {
            r = m - 1;
        }
        else
        {
            l = m;
        }
    }
    if (a[l] > v)
    {
        return -1;
    }
    return l;
}