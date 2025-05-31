#include <stdio.h>
#include <string.h>

int main()
{
    FILE *file;
    char id[10], name[100];
    int quantity;
    double price, total = 0.0;

    file = fopen("product.txt", "r");

    if (file!=NULL)
    {
        int numProducts;
        printf("Numbers of product: ");
        scanf("%d", &numProducts);

        char products[numProducts][10];
        int quantities[numProducts];

        for (int i=0; i<numProducts; ++i)
        {
            printf("Product ID and quantity (separated by a space): ");
            scanf("%s %d", products[i], &quantities[i]);
        }

        fclose(file);

        file = fopen("product.txt", "r");

        for (int i=0; i<numProducts; ++i)
        {
            while (fscanf(file, "%[^#]#%[^#]#%lf\n", id, name, &price) != EOF)
            {
                //Check IDs match
                if (strcmp(products[i], id)==0)
                {
                    double productTotal = price * quantities[i];
                    total += productTotal;
                    break;
                }
            }
            fseek(file, 0, SEEK_SET);
        }

        printf("Total: %.2f\n", total);

        fclose(file);
    }

    else
    {
        printf("Error to open file.\n");
        return 1;
    }

    return 0;
}
