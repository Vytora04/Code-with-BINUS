#include <stdio.h>

void planted(int T, int t, int results[])
{
    if (t==T)
    {
        return;
    }

    int N;
    scanf("%d", &N);

    int plant = 0;
    for (int i=0; i<N; i++)
    {
        int tree;
        scanf("%d", &tree);
        plant += tree;
    }

    results[t] = plant;

    planted(T, t+1, results);
}

int main()
{
    int T;
    scanf("%d", &T);

    int results[T];

    planted(T, 0, results);

    for (int t=0; t<T; t++)
    {
        printf("Case #%d: %d\n", t+1, results[t]);
    }

    return 0;
}
