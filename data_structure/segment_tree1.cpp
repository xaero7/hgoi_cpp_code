/*
 *  本题中的坐标是浮点类型的, 故不能将坐标直接离散.我们必须为它们建立一个对应关系,
 *  用一个整数去对应一个浮点数这样的对应关系在本题的数组y[]中。
 */
struct node
{
    int st, ed, c;      //  c: 区间被覆盖的层数, m: 区间的测度
    double m;
} ST[802];

struct line
{
    double x, y1, y2;   //  纵方向直线, x:直线横坐标, y1 y2:直线上的下面与上面的两个纵坐标
    bool s;             //  s = 1 : 直线为矩形的左边, s = 0:直线为矩形的右边
} Line[205];

double y[205], ty[205]; //  y[]整数与浮点数的对应数组; ty[]:用来求y[]的辅助数组

void build(int root, int st, int ed)
{
    ST[root].st = st;
    ST[root].ed = ed;
    ST[root].c = 0;
    ST[root].m = 0;
    if (ed - st > 1)
    {
        int mid = (st + ed) / 2;
        build(root * 2, st, mid);
        build(root * 2 + 1, mid, ed);
    }
    return ;
}

void updata(int root)
{
    if (ST[root].c > 0)
    {   //  将线段树上区间的端点分别映射到y[]数组所对应的浮点数上,由此计算出测度
        ST[root].m = y[ST[root].ed - 1] - y[ST[root].st - 1];
    }
    else if (ST[root].ed - ST[root].st == 1)
    {
        ST[root].m = 0;
    }
    else
    {
        ST[root].m = ST[root * 2].m + ST[root * 2 + 1].m;
    }
    return ;
}

void insert(int root, int st, int ed)
{
    if (st <= ST[root].st && ST[root].ed <= ed)
    {
        ST[root].c++;
        updata(root);
        return ;
    }
    if (ST[root].ed - ST[root].st == 1)
    {
        return ;    //  不出错的话 这句话就是冗余的
    }
    int mid = (ST[root].ed + ST[root].st) / 2;
    if (st < mid)
    {
        insert(root * 2, st, ed);
    }
    if (ed > mid)
    {
        insert(root * 2 + 1, st, ed);
    }
    updata(root);
    return ;
}

void Delete(int root, int st, int ed)
{
    if (st <= ST[root].st && ST[root].ed <= ed)
    {
        ST[root].c--;
        updata(root);
        return ;
    }
    if (ST[root].ed - ST[root].st == 1)
    {
        return ;    //  不出错的话 这句话就是冗余的
    }
    int mid = (ST[root].st + ST[root].ed) / 2;
    if (st < mid)
    {
        Delete(root * 2, st, ed);
    }
    if (ed > mid)
    {
        Delete(root * 2 + 1, st, ed);
    }
    updata(root);
    return ;
}

int Correspond(int n, double t)
{
    //  二分查找出浮点数t在数组y[]中的位置(此即所谓的映射关系)
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low < high)
    {
        mid = (low + high) / 2;
        if (t > y[mid])
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    return high + 1;
}

bool cmp(line l1, line l2)
{
    return l1.x < l2.x;
}

int main()
{
    int n, i, num, l, r, c = 0;
    double area, x1, x2, y1, y2;
    while (cin >> n, n)
    {
        for (i = 0; i < n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            Line[2 * i].x = x1;
            Line[2 * i].y1 = y1;
            Line[2 * i].y2 = y2;
            Line[2 * i].s = 1;
            Line[2 * i + 1].x = x2;
            Line[2 * i + 1].y1 = y1;
            Line[2 * i + 1].y2 = y2;
            Line[2 * i + 1].s = 0;
            ty[2 * i] = y1;
            ty[2 * i + 1] = y2;
        }
        n <<= 1;
        sort(Line, Line + n, cmp);
        sort(ty, ty + n);
        y[0] = ty[0];
        //  处理数组ty[]使之不含重覆元素,得到新的数组存放到数组y[]中
        for (i = num = 1; i < n; i++)
        {
            if (ty[i] != ty[i - 1])
            {
                y[num++] = ty[i];
            }
        }
        build(1, 1, num);   //  树的叶子节点与数组y[]中的元素个数相同,以便建立一一对应的关系
        area = 0;
        for (i = 0; i < n - 1; i++)
        {   //  由对应关系计算出线段两端在树中的位置
            l = Correspond(num, Line[i].y1);
            r = Correspond(num, Line[i].y2);
            if (Line[i].s)  //  插入矩形的左边
            {
                insert(1, l, r);
            }
            else            //  删除矩形的右边
            {
                Delete(1, l, r);
            }
            area += ST[1].m * (Line[i + 1].x - Line[i].x);
        }
        cout << "Test case #" << ++c << endl << "Total explored area: ";
        cout << fixed << setprecision(2) << area << endl << endl;   //  需要引入iomanip头文件
    }
    return 0;
}