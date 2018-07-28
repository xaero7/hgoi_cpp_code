const int MAXN = 100;
int phi[MAXN + 2];

int main()
{
    for (int i = 1; i <= MAXN; i++) phi[i] = i;
    for (int i = 2; i <= MAXN; i += 2) phi[i] /= 2;
    for (int i = 3; i <= MAXN; i += 2)
    {
        if (phi[i] == i)
        {
            for (int j = i; j <= MAXN; j += i)
            {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    return 0;
}