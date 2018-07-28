/**
 * 求`$a^b \mod m$`的值，`$b$`的值可以是`$10^9$`
 */
int power_mod(int a, int b, int m)
{
	int tmp = 0;
	if (b==0) return 1;
	tmp = power_mod(a, b>>1, m);
	tmp *= tmp % m;
	if (m&1) tmp = tmp*a % m;
	return tmp;
}