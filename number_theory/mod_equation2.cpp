/**
 * 已知`$a_i, m_i$`，每个`$m_i$`互质，
 * 求方程组`$x \equiv a_i \pmod{m_i}$`的最小非负整数根`$x$`
 */
LL CRT(LL a[], LL m[], LL cnt)
{
	LL M = 1, res = 0, x, y;
	for (int i = 0; i < cnt; i++) M *= m[i];
	for (int i = 0; i < cnt; i++)
	{
		LL Mi = M / m[i];
		LL g = extended_euclid(Mi, m[i], x, y);
		res = (res + Mi * x * a[i]) % M;
	}
	return (M + res % M) % M;  //最小非负整数
}