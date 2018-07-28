/*
 *  拓扑排序
 *  INIT:edge[][]置为图的邻接矩阵;cnt[0...i...n-1]:顶点i的入度。
 */
const int MAXV = 1010;

int edge[MAXV][MAXV];
int cnt[MAXV];

void TopoOrder(int n)
{
    int i, top = -1;
    for (i = 0; i < n; ++i)
    {
        if (cnt[i] == 0)
        {   //  下标模拟堆栈
            cnt[i] = top;
            top = i;
        }
    }
    for (i = 0; i < n; i++)
    {
        if (top == -1)
        {
            printf("存在回路\n");
            return ;
        }
        else
        {
            int j = top;
            top = cnt[top];
            printf("%d", j);
            for (int k = 0; k < n; k++)
            {
                if (edge[j][k] && (--cnt[k]) == 0)
                {
                    cnt[k] = top;
                    top = k;
                }
            }
        }
    }
}