/*
 *  INIT: ar[]置为0;
 *  CALL: add(i, v): 将i点的值加v; sum(i): 求[1, i]的和;
 */
#define typev int   //  type of res

const int N = 1010;

typev ar[N];        //  index: 1 ~ N

int lowb(int t)
{
    return t & (-t);
}

void add(int i, typev v)
{
    for (; i < N; ar[i] += v, i += lowb(i));
    return ;
}

typev sum(int i)
{
    typev s = 0;
    for (; i > 0; s += ar[i], i -= lowb(i));
    return s;
}