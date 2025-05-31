#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 500

int main()
{
    FILE *file = fopen("data.txt", "r");
    if (file == NULL)
    {
        printf("Error opening data file.\n");
        return 1;
    }

    int T;
    scanf("%d", &T);

    char keyword[MAX_LENGTH];
    for (int t=1; t<=T; t++)
    {
        rewind(file);
        scanf("%s", keyword);

        char line[MAX_LENGTH];
        char result[MAX_LENGTH] = "Not Found";
        int found = 0;

        while (fscanf(file, "%[^#]#%[^\n]\n", line, result) == 2)
        {
            if (strstr(line, keyword)!=NULL)
            {
                printf("Case %d: %s\n", t, result);
                found = 1;
                break;
            }
        }

        if (!found)
        {
            printf("Case %d: %s\n", t, result);
        }
    }

    fclose(file);
    return 0;
}
