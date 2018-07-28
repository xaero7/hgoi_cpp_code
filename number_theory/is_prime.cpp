/**
 * 判断`$n$`是否是素数，`$O(\sqrt{n})$`复杂度
 */
for (int i = 2; i <= sqrt(n); i++)
{
	if (n % i == 0)
	{
		return false;
	}
}
return true;