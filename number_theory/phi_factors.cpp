/**
 * 分解质因数法求解，get_factors(n)函数见上
 */
get_factors(n);
int ret = n;
for (int i = 0; i < fatCnt; i++)
{
	ret = (int)(ret / factor[i][0] * (factor[i][0] - 1));
}
 