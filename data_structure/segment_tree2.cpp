struct node
{
    int st, ed, m, lbd, rbd;
    int sequence_line, count;
} ST[40005];

void build(int st, int ed, int v)       //  建树,区间为[st, ed]
{
    ST[v].st = st;
    ST[v].ed = ed;
    ST[v].m = ST[v].lbd = ST[v].rbd = 0;
    ST[v].sequence_line = ST[v].count = 0;
    if (ed - st > 1)
    {
        int mid = (st + ed) / 2;
        build(st, mid, 2 * v + 1);
        build(mid, ed, 2 * v + 2);
    }
    return ;
}

void UpData(int v)                      //  更新结点区间的测度
{
    if (ST[v].count > 0)
    {
        ST[v].m = ST[v].ed - ST[v].st;
        ST[v].lbd = ST[v].rbd = 1;
        ST[v].sequence_line = 1;
        return ;
    }
    if (ST[v].ed - ST[v].st == 1)
    {
        ST[v].m = 0;
        ST[v].lbd = ST[v].rbd = 0;
        ST[v].sequence_line = 0;
    }
    else
    {
        int left = 2 * v + 1, right = 2 * v + 2;
        ST[v].m = ST[left].m + ST[right].m;
        ST[v].sequence_line = ST[left].sequence_line + ST[right].sequence_line - (ST[left].rbd & ST[right].lbd);
        ST[v].lbd = ST[left].lbd;
        ST[v].rbd = ST[right].rbd;
    }
    return ;
}

void insert(int st, int ed, int v)
{
    if (st <= ST[v].st && ed >= ST[v].ed)
    {
        ST[v].count++;
        UpData(v);
        return ;
    }
    int mid = (ST[v].st + ST[v].ed) / 2;
    if (st < mid)
    {
        insert(st, ed, 2 * v + 1);
    }
    if (ed > mid)
    {
        insert(st, ed, 2 * v + 2);
    }
    UpData(v);
    return ;
}

void Delete(int st, int ed, int v)
{
    if (st <= ST[v].st && ed >= ST[v].ed)
    {
        ST[v].count--;
        UpData(v);
        return ;
    }
    int mid = (ST[v].st + ST[v].ed) / 2;
    if (st < mid)
    {
        Delete(st, ed, 2 * v + 1);
    }
    if (ed > mid)
    {
        Delete(st, ed, 2 * v + 2);
    }
    UpData(v);
    return ;
}

struct line
{
    int x, y1, y2;  //  y1 < y2
    bool d;         //  d=true表示该线段为矩形左边,d=false表示该线段为矩形的右边
} a[10003];

bool cmp(line t1, line t2)  //  为线段排序的函数,方便从左向右的扫描
{
    return t1.x < t2.x;
}

void cal_C(int n);

int main()
{
    int n, x1, x2, y1, y2, i, j, suby, upy;
    while (scanf("%d",&n) != EOF)
    {
        j = 0;
        suby = 10000;
        upy = -10000;
        for (i = 0; i < n; i++)
        {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            a[j].x = x1;
            a[j].y1 = y1;
            a[j].y2 = y2;
            a[j].d = 1;
            j++;
            a[j].x = x2;
            a[j].y1 = y1;
            a[j].y2 = y2;
            a[j].d = 0;
            j++;
            if (suby > y1)
            {
                suby = y1;
            }
            if (upy < y2)
            {
                upy = y2;
            }
        }
        sort(a, a + j, cmp);
        build(suby, upy, 0);
        cal_C(j);
    }
    return 0;
}

void cal_C(int n)
{
    int i, t2, sum = 0;
    t2 = 0;
    a[n] = a[n - 1];
    for (i = 0; i < n; i++)
    {
        if (a[i].d == 1)
        {
            insert(a[i].y1, a[i].y2, 0);
        }
        else
        {
            Delete(a[i].y1, a[i].y2, 0);
        }
        sum += ST[0].sequence_line * (a[i + 1].x - a[i].x) * 2;
        sum += abs(ST[0].m - t2);
        t2 = ST[0].m;
    }
    printf("%d\n", sum);
}