void readin(int &m)
{
    char ch;
    int flag = 0;
    while ((ch = getchar()) < '0' || ch > '9')
    {
        if (ch == '-')
        {
            flag = 1;
        }
    }
    for (m = 0; ch >= '0' && ch <= '9'; ch = getchar())
    {
        m = m * 10 + ch - '0';
    }
    if (flag)
    {
        m *= -1;
    }
}