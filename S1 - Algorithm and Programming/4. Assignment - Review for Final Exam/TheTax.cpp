#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float CalculateTax(int pkp)
{
    if (pkp<=60000000)
    {
        return pkp*0.05;
    }
    else if (pkp<=250000000)
    {
        return (60000000*0.05) + ((pkp-60000000)*0.15);
    }
    else if (pkp<=500000000)
    {
        return (60000000*0.05)+ (190000000*0.15) + ((pkp-250000000)*0.25);
    }
    else if (pkp<=5000000000)
    {
        return (60000000*0.05) + (190000000*0.15) + (250000000*0.25) + ((pkp-500000000)*0.30);
    }
    else
    {
        return (60000000*0.05) + (190000000*0.15) + (250000000*0.25) + (4500000000*0.30) + ((pkp-5000000000)*0.35);
    }
}

int main()
{
    FILE *file = fopen("employee.txt", "r");

    if (file==NULL)
    {
        printf("Error opening the file!\n");
        return 1;
    }

    char line[9000];
    while (fgets(line, sizeof(line), file))
    {
        char *name = strtok(line, "#");
        char *status = strtok(NULL, "#");
        float monthly_payroll = atof(strtok(NULL, "#"));

        int ptkp = 0;

        if (strcmp(status, "TK") == 0)
        {
            ptkp = 54000000;
        }
        else if (strcmp(status, "K/0") == 0)
        {
            ptkp = 58500000;
        }
        else if (strcmp(status, "K/1") == 0)
        {
            ptkp = 63000000;
        }
        else if (strcmp(status, "K/2") == 0)
        {
            ptkp = 67500000;
        }
        else if (strcmp(status, "K/3") == 0)
        {
            ptkp = 72000000;
        }
        else
        {
            printf("Invalid tax status for %s.\n", name);
            continue;
        }

        float pkp = 12 * monthly_payroll - ptkp;

        if (pkp<0)
            pkp = 0;

        float tax = CalculateTax(pkp);
        float monthly_thp = monthly_payroll - (tax/12); // Corrected calculation

        printf("%s - %.0f\n", name, monthly_thp);
    }

    fclose(file);

    return 0;
}
