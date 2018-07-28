/*
 *  取第k个元素
 *  k = 0 ... n - 1,平均复杂度O(n) 注意a[]中的顺序被改变
 */
#define comp(a,b) ((a) < (b))
typedef int elem_t;

elem_t kth_element(int n, elem_t *a, int k)
{   //  a[0 ... n-1]
    elem_t t, key;
    int l = 0, r = n - 1, i, j;
    while (l < r)
    {
        for (key = a[((i = l - 1) + (j = r + 1)) >> 1]; i < j;)
        {
            for (j--; comp(key, a[j]); j--);
            for (i++; comp(a[i], key); i++);
            if (i < j)
            {
                t = a[i], a[i] = a[j], a[j] = t;
            }
        }
        if (k > j)
        {
            l = j + 1;
        }
        else
        {
            r = j;
        }
    }
    return a[k];
}