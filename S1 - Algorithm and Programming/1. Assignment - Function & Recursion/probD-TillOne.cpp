#include <stdio.h>

int F(long long N)
{
    if (N == 1)
        return 1;
    if (N%2 == 0)
        return F(N/2);
    else
        return F(N-1) + F(N+1);
}

int main()
{
    int T;
    scanf("%d", &T);

    long long N[T];

    for (int t=0; t<T; t++)
    {
        scanf("%d", &N[t]);
    }

    for (int t=0; t<T; t++)
    {
        printf("Case #%d: %d\n", t+1, F(N[t]));
    }

    return 0;
}
