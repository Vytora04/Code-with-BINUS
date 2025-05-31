#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50

struct DictionaryEntry
{
    char indonesian[MAX_LENGTH];
    char english[MAX_LENGTH];
};

void displayData(struct DictionaryEntry data[], int count, const char *order)
{
    printf("Sorted data in %s order:\n", order);
    for (int i=0; i<count; i++)
    {
        printf("%s=%s\n", data[i].indonesian, data[i].english);
    }
}

void bubbleSortASC(struct DictionaryEntry data[], int count)
{
    for (int i=0; i<count-1; i++)
    {
        for (int j=0; j<count-i-1; j++)
        {
            if (strcmp(data[j].indonesian, data[j+1].indonesian)>0)
            {
                struct DictionaryEntry temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

void bubbleSortDES(struct DictionaryEntry data[], int count)
{
    for (int i=0; i<count-1; i++)
    {
        for (int j=0; j<count-i-1; j++)
        {
            if (strcmp(data[j].indonesian, data[j+1].indonesian)<0)
            {
                struct DictionaryEntry temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
}

void saveToFile(struct DictionaryEntry data[], int count)
{
    FILE *file = fopen("dictionary.txt", "w");
    for (int i=0; i<count; i++)
    {
        fprintf(file, "%s=%s\n", data[i].indonesian, data[i].english);
    }
    fclose(file);
}

int main()
{
    FILE *file = fopen("dictionary.txt", "r");
    char line[MAX_LENGTH];

    printf("Data from dictionary.txt:\n");
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }
    fclose(file);

    while (1)
    {
        printf("\nMenu:\n");
        printf("1. Input a pair of Indonesian and English word\n");
        printf("2. Sort the data in Ascending Order\n");
        printf("3. Sort the data in Descending Order\n");
        printf("4. Save and Exit\n");
        printf("\nInput your choice: ");

        int choice;
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
            case 1:
            {
                struct DictionaryEntry entry;
                printf("Enter Indonesian word: ");
                scanf("%s", entry.indonesian);
                printf("Enter English word: ");
                scanf("%s", entry.english);

                if (strlen(entry.indonesian)<=MAX_LENGTH && strlen(entry.english)<=MAX_LENGTH)
                {
                    FILE *file = fopen("dictionary.txt", "a");
                    fprintf(file, "%s=%s\n", entry.indonesian, entry.english);
                    fclose(file);
                }
                else
                {
                    printf("Maximum length is 50 characters.\n");
                }

                break;
            }
            case 2:
            {
                FILE *file = fopen("dictionary.txt", "r");
                int count = 0;
                struct DictionaryEntry data[MAX_LENGTH];
                while (fscanf(file, "%[^=]=%[^\n]\n", data[count].indonesian, data[count].english) == 2)
                {
                    count++;
                }
                fclose(file);

                bubbleSortASC(data, count);
                displayData(data, count, "ascending");
                break;
            }
            case 3:
            {
                FILE *file = fopen("dictionary.txt", "r");
                int count = 0;
                struct DictionaryEntry data[MAX_LENGTH];
                while (fscanf(file, "%[^=]=%[^\n]\n", data[count].indonesian, data[count].english) == 2)
                {
                    count++;
                }
                fclose(file);

                bubbleSortDES(data, count);
                displayData(data, count, "descending");
                break;
            }
            case 4:
            {
                FILE *file = fopen("dictionary.txt", "r");
                int count = 0;
                struct DictionaryEntry data[MAX_LENGTH];
                while (fscanf(file, "%[^=]=%[^\n]\n", data[count].indonesian, data[count].english) == 2)
                {
                    count++;
                }
                fclose(file);

                saveToFile(data, count);
                return 0;
            }
            default:
                printf("Invalid choice. Please input a valid choice.\n");
                break;
        }
    }

    return 0;
}
