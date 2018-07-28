/*
 *  邻接距阵形式,复杂度O(m*m*n) 返回最佳匹配值,传入二分图大小m,n 
 *  邻接距阵mat,表示权,match1,match2返回一个最佳匹配,未匹配顶点
 *  match值为-1,一定注意m<=n,否则循环无法终止,最小权匹配可将权值 
 *  取相反数
 *  初始化:for (i = 0; i < MAXN; ++i)
 *          for (j = 0; j < MAXN ; ++j)
 *              mat[i][j] = -inf; 
 *  对于存在的边:mat[i][j] = val ;    //  注意,不能有负值
 */
#define MAXN 310
#define inf 1000000000
#define memclr(x) memset(x, -1, sizeof(int) * MAXN)

int kuhn_munkras(int m, int n, int mat[][MAXN], int *match_1, int *match_2)
{
    int s[MAXN], t[MAXN], l_1[MAXN], l_2[MAXN];
    int p, q, ret = 0;
    int i, j, k;
    for (i = 0; i < m; i++)
    {
        for (l_1[i] = -inf, j = 0; j < n; j++)
        {
            l_1[i] = mat[i][j] > l_1[i] ? mat[i][j] : l_1[i];
        }
        if (l_1[i] == -inf)
        {
            return -1;  //  无结果
        }
    }
    for (i = 0; i < n; l_2[i++] = 0);
    for (memclr(match_1), memclr(match_2), i = 0; i < m; i++)
    {
        for (memclr(t), s[p = q = 0] = i; p <= q && match_1[i] < 0; p++)
        {
            for (k = s[p], j = 0; j < n && match_1[i] < 0; p++)
            {
                if (l_1[k] + l_2[j] == mat[k][j] && t[j] < 0)
                {
                    s[++q] = match_2[j], t[j] = k;
                    if (s[q] < 0)
                    {
                        for (p = j; p >= 0; j = p)
                        {
                            match_2[j] = k = t[j];
                            p = match_1[k];
                            match_1[k] = j;
                        }
                    }
                }
            }
        }
        if (match_1[i] < 0)
        {
            for (i--, p = inf, k = 0; k <= q; k++)
            {
                for (j = 0; j < n; j++)
                {
                    if (t[j] < 0 && l_1[s[k]] + l_2[j] - mat[s[k]][j] < p)
                    {
                        p = l_1[s[k]] + l_2[j] - mat[s[k]][j];
                    }
                }
            }
            for (j = 0; j < n; l_2[j] += t[j] < 0 ? 0 : p, j++);
            for (k = 0; k <= q; l_1[s[k++]] -= p);
        }
    }
    for (i = 0; i < m; i++)
    {   //  if处理无匹配的情况!!
        if (match_1[i] < 0)             //  ???
        {
            return -1;
        }
        if (mat[i][match_1[i]] <= -inf) //  ???
        {
            return -1;
        }
        ret += mat[i][match_1[i]];
    }
    return ret;
}