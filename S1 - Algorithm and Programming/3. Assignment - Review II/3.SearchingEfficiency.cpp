#include <stdio.h>
#include <string.h>

typedef struct
{
    char studentName[101];
    int studentScore;
} Student;

int linearSearch(Student students[], int N, char searchName[], int *linearSteps)
{
    for (int i = 0; i < N; i++)
    {
        (*linearSteps)++;
        if (strcasecmp(students[i].studentName, searchName) == 0)
        {
            return students[i].studentScore;
        }
    }
    return -1;
}

int binarySearch(Student students[], int left, int right, char searchName[], int *binarySteps)
{
    while (left <= right)
    {
        (*binarySteps)++;
        int mid = left+(right-left)/2;
        int target = strcasecmp(students[mid].studentName, searchName);

        if (target==0)
        {
            return students[mid].studentScore;
        }
        else if (target<0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);

    Student studentArray[T];

    char F[51];
    for (int i=0; i<T; i++)
    {
        scanf("%[^#]#%d\n", F, &studentArray[i].studentScore);
        strcpy(studentArray[i].studentName, F);
    }

    int N;
    scanf("%d", &N);

    for (int i=0; i<N; i++)
    {
        char searchName[55];
        scanf("%s", searchName);

        int linearSteps = 0, binarySteps = 0;
        int linearResult = linearSearch(studentArray, N, searchName, &linearSteps);
        int binaryResult = binarySearch(studentArray, 0, N-1, searchName, &binarySteps);

        if (linearResult!=-1 && binaryResult!=-1)
        {
            printf("%d ", linearResult);
            if (linearSteps==binarySteps)
            {
                printf("SAME\n");
            }
            else if (binarySteps<linearSteps)
            {
                printf("%d\n", linearSteps-binarySteps);
            }
            else
            {
                printf("-1\n");
            }
        }
        else
        {
            printf("-1 -1\n");
        }
    }

    return 0;
}
