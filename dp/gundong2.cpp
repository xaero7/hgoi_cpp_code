int main()
{
    int i;
    long long d[3];
    d[0] = 1;
    d[1] = 1;
    for(i = 2; i < 80; i++)
    {
        d[i % 3] = d[(i - 1) % 3] + d[(i - 2) % 3];
    }
    printf("%lld\n", d[79%3]);
    return 0;
}