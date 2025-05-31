#include <stdio.h>
#include <stdlib.h>

int CalculateBombs(int n, int x)
{
    if (n<=1)
    {
        return 1;
    }
    else
    {
        return n + CalculateBombs(n-1, x+1) + CalculateBombs(n-2, x+2);
    }
}

int main()
{
    int N, X;

    scanf("%d %d", &N, &X);

    if (N<1 || X<1)
    {
        printf("Must be positive numbers!\n");
    }

    else if (N>=25 || X>=25)
    {
        printf("Must not exceeding 25!\n");
    }

    else
    {
        printf("%d\n", CalculateBombs(N, X));
    }

    return 0;
}
