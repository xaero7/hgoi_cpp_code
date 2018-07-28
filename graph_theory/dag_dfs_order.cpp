/*
 * DAG(有向无环图)的深度优先搜索标记
 * INIT:edge[][]邻接矩阵；pre[], post[], tag全置0
 * CALL:dfsTag(i, n);   pre/post:开始/结束时间
 */

const int V = 1010;
int edge[V][V];
int pre[V];
int post[V];
int tag;

void dfsTag(int cur, int n)
{
    //vertex:0 ~ n - 1
    pre[cur] = ++tag;
    for (int i = 0; i < n; i++)
    {
        if (edge[cur][i])
        {
            if (0 == pre[i])
            {
                std::cout << "Three Edge!" << '\n';
                dfsTag(i, n);
            }
            else
            {
                if (0 == post[i])
                {
                    std::cout << "Back Edge!" << '\n';
                }
                else if (pre[i] > pre[cur])
                {
                    std::cout << "Down Edge!" << '\n';
                }
                else
                {
                    std::cout << "Cross Edge!" << '\n';
                }
            }
        }
    }
    post[cur] = ++tag;
    return ;
}