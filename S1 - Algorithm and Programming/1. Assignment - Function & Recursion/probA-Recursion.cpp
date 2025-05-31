#include <stdio.h>

int calculate(int N, int *calls)
{
    if (N == 0) return 1;
    if (N == 1) return 2;

    int f[N + 1];
    f[0] = 1;
    f[1] = 2;
    *calls = 0;

    for (int i=2; i<=N; i++)
    {
        f[i] = f[i - 1] + i + f[i - 2] + i - 2;
        if (i % 3 == 0 && i % 5 != 0) (*calls)++;
        if (i % 5 == 0) f[i] = i * 2;
    }

    return f[N];
}

int main()
{
    int T;
    scanf("%d", &T);

    int N[T];

    for (int t = 0; t < T; t++)
    {
        scanf("%d", &N[t]);
    }

    for (int t = 0; t < T; t++)
    {
        int calls;
        int result = calculate(N[t], &calls);

        printf("Case #%d: %d %d\n", t+1, result, calls);
    }

    return 0;
}
