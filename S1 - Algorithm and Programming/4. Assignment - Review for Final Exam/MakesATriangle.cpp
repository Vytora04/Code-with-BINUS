#include <stdio.h>

// Function to perform bubble sort on an array
void bubble_sort(int n, int arr[])
{
    for (int i=0; i<n-1; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (arr[i]>arr[j])
            {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main()
{
    int N;
    scanf("%d", &N);

    if (N<3)
    {
        printf("NO\n");
    }

    else
    {
        int segments[N];
        for (int i=0; i<N; i++)
        {
            scanf("%d", &segments[i]);
        }

        bubble_sort(N, segments); // Sorting the line segments using the bubble sort algorithm

        // Checking for the existence of a triplet (a, b, c) such that a + b > c
        int formTriangle = 0; // Flag to track if exactly three line is found
        for (int i=0; i<N-2; i++)
        {
            if ((segments[i]+segments[i+1])>segments[i+2])
            {
                formTriangle = 1;
                break;
            }
        }

        // Output result
        if (formTriangle)
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
