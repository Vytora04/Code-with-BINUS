#include <stdio.h>
#include <string.h>

int main()
{
    FILE *file = fopen("testdata.in", "r");
    if (file == NULL)
    {
        printf("Error opening testdata.in");
        return 1;
    }

    int x, y, n;
    fscanf(file, "%d %d\n", &x, &y);
    fscanf(file, "%d\n", &n);

    char direction[20];

    const char right[10]="RIGHT";
    const char left[10]="LEFT";
    const char up[10]="UP";
    const char down[10]="DOWN";

    int steps;
    for (int i=0; i<n; i++)
    {
        fscanf(file, "%[^#]#%d\n", direction, &steps);
        if (strcmp(direction, right) == 0)
        {
            x+=steps;
        }
        if (strcmp(direction, left) == 0)
        {
            x-=steps;
        }
        if (strcmp(direction, up) == 0)
        {
            y+=steps;
        }
        if (strcmp(direction, down) == 0)
        {
            y-=steps;
        }

    }

    if (x>25)
    {
        x-=25;
    }
    else if(x<1)
    {
        x+=25;
    }

    if (y>25)
    {
        y-=25;
    }
    else if (y<1)
    {
        y+=25;
    }

    char prize[10];
    if (x == y)
    {
        strcpy(prize, "PrizeA");
    }
    else if (x % 2 == 1)
    {
        strcpy(prize, "PrizeB");
    }
    else if (x % 2 == 0)
    {
        strcpy(prize, "PrizeC");
    }

    // Print the final coordinate and the prize won
    printf("%d %d %s\n", x, y, prize);

    fclose(file);
    return 0;
}
