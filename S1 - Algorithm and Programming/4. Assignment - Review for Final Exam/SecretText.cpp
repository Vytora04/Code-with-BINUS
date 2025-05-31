#include <stdio.h>
#include <string.h>

int Coordinate(char S[])
{
    int total = 0;

    for (int i=0; i<strlen(S); i++)
    {
        if (S[i]>='A' && S[i]<='Z')
            total += (S[i]-'A'+1);
        else if (S[i]>='a' && S[i]<='z')
            total += (S[i]-'a'+1);
    }

    return total;
}

int main()
{
    int HH, MM, n1, n2;
    char temp[10005], word[10][10005];

    for (int i=0; i<2; i++)
    {
        scanf("%d:%d>%[^\n]", &HH, &MM, temp); getchar();

        int count = 0;

        char *token;
        token = strtok(temp, " ");

        while (token!=NULL)
        {
            strcpy(word[count], token);
            count++;
            token = strtok(NULL, " ");
        }

        int temp = MM/10;
        int result = Coordinate(word[temp]);

        temp = MM % 10;
        result += Coordinate(word[temp]);

        while (result>180)
            result-=180;

        if (HH<=0 || HH>=12)
            result *= -1;

        if (i==1)
            n2 = result;
        else
            n1 = result;
    }

    printf("%d,%d\n", n1, n2);

    return 0;
}
