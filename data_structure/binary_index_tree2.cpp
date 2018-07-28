/*
 *  INIT: c[][]置为0; Row,Col要赋初值 
 */
const int N = 10000;

int c[N][N];
int Row, Col;

inline int Lowbit(const int &x)
{   //  x > 0
    return x & (-x);
}

int Sum(int i, int j)
{
    int tempj, sum = 0;
    while (i > 0)
    {
        tempj = j;
        while (tempj > 0)
        {
            sum += c[i][tempj];
            tempj -= Lowbit(tempj);
        }
        i -= Lowbit(i);
    }
    return sum;
}

void Update(int i, int j, int num)
{
    int tempj;
    while (i <= Row)
    {
        tempj = j;
        while (tempj <= Col)
        {
            c[i][tempj] += num;
            tempj += Lowbit(tempj);
        }
        i += Lowbit(i);
    }
    return ;
}