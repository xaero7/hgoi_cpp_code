/*
 *  左孩子右兄弟
 *  INIT: init();
 */
const int N = 1010;
int top;

struct trie
{
    char c;
    int l, r, rk;
} tree[N];

void init()
{
    top = 1;
    memset(tree, 0, sizeof(tree[0]));
}

int sear(char *s)   //  失败返回0
{
    int rt;
    for (rt = 0; *s; ++s)
    {
        for (rt = tree[rt].l; rt; rt = tree[rt].r)
        {
            if (tree[rt].c == *s)
            {
                break;
            }
        }
        if (rt == 0)
        {
            return 0;
        }
    }
    return tree[rt].rk;
}

void insert(char *s, int rk = 1)    //  rk: 权或者标记
{
    int i, rt;
    for (rt = 0; *s; ++s, rt = i)
    {
        for (i = tree[rt].l; i; i = tree[i].r)
        {
            if (tree[i].c == *s)
            {
                break;
            }
        }
        if (i == 0)
        {
            tree[top].r = tree[rt].l;
            tree[top].l = 0;
            tree[top].c = *s;
            tree[top].rk = 0;
            tree[rt].l = top;
            i = top++;
        }
    }
    tree[rt].rk = rk;
    return ;
}

void delt(char *s)  //  假定s已经存在,只做标记
{
    int rt;
    for (rt = 0; *s; ++s)
    {
        for (rt = tree[rt].l; rt; rt = tree[rt].r)
        {
            if (tree[rt].c == *s)
            {
                break;
            }
        }
        tree[rt].rk = 0;
    }
    return ;
}

int profix(char *s) //  最长前缀
{
    int rt = 0, lv;
    for (lv = 0; *s; ++s, ++lv)
    {
        for (rt = tree[rt].l; rt; rt = tree[rt].r)
        {
            if (tree[rt].c == *s)
            {
                break;
            }
        }
        if (rt == 0)
        {
            break;
        }
    }
    return lv;
}