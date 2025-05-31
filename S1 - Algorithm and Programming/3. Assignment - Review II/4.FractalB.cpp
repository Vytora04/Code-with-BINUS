#include <stdio.h>

long long asteriskCount = 0;
long long memory[101] = {0};

long long fractal_B(int x)
{
    if (x<=0)
    {
        return 0;
    }
    else if (memory[x]!=0)
    {
        return memory[x];
    }
    else
    {
        memory[x] = fractal_B(x-1) + x + fractal_B(x-2);
        return memory[x];
    }
}

int main()
{
    int X;
    scanf("%d", &X);

    asteriskCount = fractal_B(X);

    printf("%lld\n", asteriskCount);

    return 0;
}

//Time Complexity Issues
/*
#include <stdio.h>

long long asteriskCount = 0;

void fractal_B(int x)
{
    int i;
    if (x <= 0)
        return;
    else
    {
        fractal_B(x - 1);
        for (i=1; i<=x; i++)
        {
            asteriskCount++;
        }
        fractal_B(x-2);
    }
}

int main()
{
    int X;
    scanf("%d", &X);

    fractal_B(X);

    printf("%lld\n", asteriskCount);

    return 0;
}
*/
