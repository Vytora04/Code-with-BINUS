#include <stdio.h>

int main()
{
    int n = 11;

    while (n <= 188)
    {
        if (n % 2 != 0)
        {
            printf("%d\n", n);
        }
        n++;
    }

    return 0;
}
