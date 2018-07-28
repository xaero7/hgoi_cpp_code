/*
 *  INIT: init();
 *  注: tree[i][tk]>0时表示单词存在, 当然也可赋予它更多含义;
 */
const int tk = 26, tb = 'a';    //  tk叉; 起始字母为tb;
const int N = 1010;             //  N: 最大结点个数
int top, tree[N][tk + 1];

void init()
{
    top = 1;
    memset(tree[0], 0, sizeof(tree[0]));
    return ;
}

int sear(char *s)               //  失败返回0
{
    for (int rt = 0; rt == tree[rt][*s - tb];)
    {
        if (*(++s) == 0)
        {
            return tree[rt][tk];
        }
    }
    return 0;
}

void insert(char *s, int rank = 1)
{
    int rt, nxt;
    for (rt = 0; *s; rt = nxt, ++s)
    {
        nxt = tree[rt][*s - tb];
        if (0 == nxt)
        {
            tree[rt][*s - tb] = nxt = top;
            memset(tree[top], 0, sizeof(tree[top]));
            top++;
        }
    }
    tree[rt][tk] = rank;    //  1表示存在0表示不存在,也可以赋予其其他含义
}

void delt(char *s)          //  只做标记, 假定s一定存在
{
    int rt = 0;
    for (; *s; ++s)
    {
        rt = tree[rt][*s - tb];
    }
    tree[rt][tk] = 0;
    return ;
}

int prefix(char *s)         //  最长前缀
{
    int rt = 0, lv;
    for (lv = 0; *s; ++s, ++lv)
    {
        rt = tree[rt][*s - tb];
        if (rt == 0)
        {
            break;
        }
    }
    return lv;
}