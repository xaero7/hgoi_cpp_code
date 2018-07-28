int main()
{
    int i;
    long long d[80];
    d[0] = 1;
    d[1] = 1;
    for(i = 2; i < 80; i++)
    {
        d[i] = d[i - 1] + d[i - 2];
    }
    printf("%lld\n",d[79]);
    return 0;
}