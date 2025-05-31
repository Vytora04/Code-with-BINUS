#include <stdio.h>
#include <string.h>

struct Address
{
    char street[100];
    int number;
    char city[100];
    char province[100];
};

struct DateOfBirth
{
    int date, month, year;
};

struct Student
{
    int id;
    char name[100];
    struct Address LOC;
    struct DateOfBirth DOB;
};

int main()
{
    int N;
    printf("Number of student to input: ");
    scanf("%d", &N);
    struct Student students[N];

    for (int i=0; i<N; i++)
    {
        printf("\nStudent no. %d Data\n", i+1);

        printf("Student number: ");
        scanf("%d", &students[i].id);

        printf("Name: ");
        scanf("%s", &students[i].name);
        getchar();

        printf("\nAddress\n");
        printf("Street name: ");
        fgets(students[i].LOC.street, 100, stdin);
        students[i].LOC.street[strcspn(students[i].LOC.street, "\n")] = 0;

        printf("Number: ");
        scanf("%d", &students[i].LOC.number);

        printf("City: ");
        getchar();
        fgets(students[i].LOC.city, 100, stdin);
        students[i].LOC.city[strcspn(students[i].LOC.city, "\n")] = 0;

        printf("Province: ");
        fgets(students[i].LOC.province, 100, stdin);
        students[i].LOC.province[strcspn(students[i].LOC.province, "\n")] = 0;

        printf("\nDate of Birth\n");
        printf("Date: ");
        scanf("%d", &students[i].DOB.date);

        printf("Month: ");
        scanf("%d", &students[i].DOB.month);

        printf("Year: ");
        scanf("%d", &students[i].DOB.year);

        printf("\n");
    }

    printf("Student's Data\n");

    for (int i=0; i<N; i++)
    {
        printf("Student %d:\n", i+1);
        printf("Student number: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Address: %d %s, %s, %s\n", students[i].LOC.number, students[i].LOC.street, students[i].LOC.city, students[i].LOC.province);
        printf("Date of Birth: %d/%d/%d\n", students[i].DOB.date, students[i].DOB.month, students[i].DOB.year);
        printf("\n");
    }

    return 0;
}
