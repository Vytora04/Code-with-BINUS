// Library
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 4001 // Macro sets for the size arrays used in the program.

// Function to wait for a key press
void PressAnyKey() // 4 lines
{
    printf("Press any key to continue..."); // Wait for a key press
    getch(); // Respond to any key
}

// Function to clear the console screen based on the operating system
void ClearScreen() // 8 lines
{
    #if defined(_WIN32) || defined(_WIN64) // Windows
        system("CLS");
    #else // Unix-like systems
        system("CLEAR");
    #endif // End the function
}

// Define a structure to hold the data of the file
typedef struct variables // 6 lines
{
    char location[SIZE], city[SIZE];
    unsigned long long int price;
    unsigned int rooms, bathrooms, carparks;
    char type[SIZE], furnish[SIZE];
} data;

// Custom case-insensitive substring search (Haystack = Full word | Needle = Partial word)
char* strcasestr(const char* haystack, const char* needle) // 21 lines
{
    while(*haystack)
    {
        const char* hay_ptr = haystack;
        const char* needle_ptr = needle;

        while(*needle_ptr && (char)(('A' <= *hay_ptr && *hay_ptr <= 'Z') ? (*hay_ptr + 32) : *hay_ptr) ==
              (char)(('A' <= *needle_ptr && *needle_ptr <= 'Z') ? (*needle_ptr + 32) : *needle_ptr))
        {
            hay_ptr++;
            needle_ptr++;
        }

        if(!*needle_ptr)
            return (char*)haystack;

        haystack++;
    }

    return NULL;
}

// Function to specifically show the menu of the program
void menu() // 9 lines
{
    puts("What do you want to do");
    puts("1. Display Data");
    puts("2. Search Data");
    puts("3. Sort Data");
    puts("4. Export Data");
    puts("5. Exit");
}

// Function to display data based on the number of rows
void DisplayData(int choice, data* rows, int totalRows) // 38 lines
{
    int N; // Declare a variable to store the number of rows to be displayed.

    // Prompt user for input integer until a positive integer is accepted
    do
    {
        printf("Number of rows: "); // Prompt the user to input the number
        scanf("%d", &N); // Scan the number of rows to be displayed
        while(getchar()!='\n'); // Clear the input buffer

        if(N<=0) // Check if the input is not a positive integer or is zero
        {
            printf("\nMust be a positive integer. Please input again!\n"); // Handle invalid input
            while(getchar()!='\n'); // Clear the input buffer to avoid an infinite loop
            PressAnyKey(); // Call function to wait for a key press
            ClearScreen(); // Call function to clear screen

            // Re-display everything after selecting menu 1
            menu();
            printf("Your choice: %d\n", choice);
        }
    }
    while(N<=0); // Continue looping until a valid positive integer is entered

    // Check whether N is more than totalRows. Set N=totalRows if exceeds
    if(N>=totalRows)
        N=totalRows; // Set N as total rows

    // Read and print N rows of data
    printf("\n%-30s%-16s%-15s%-12s%-12s%-12s%-12s%-s\n", "Location", "City", "Price", "Rooms", "Bathrooms", "Carparks", "Type", "Furnish");

    // Display N rows of data
    for(int i=0; i<N; ++i)
    {
        printf("%-30s%-16s%-15llu%-12u%-12u%-12u%-12s%-s\n", rows[i].location, rows[i].city, rows[i].price,
               rows[i].rooms, rows[i].bathrooms, rows[i].carparks, rows[i].type, rows[i].furnish);
    }
}

// Function to display data based on selection
void SelectRow(int choice, data* rows, int totalRows) // 124 lines
{
    char column[SIZE], queryvalue[SIZE]; // Declare variables to store user input

    // Prompt user for input section
    do
    {
        printf("Choose column: "); // Prompt user to choose column
        scanf("%s", column); // Read the column choice from the user
        while(getchar()!='\n'); // Clear the input buffer

        // Check if the specified column exists in the header
        int columnFound = 0; // Declare a variable to store whether the column is found
        for (int i=0; i<totalRows; ++i)
        {
            // Compare the chosen column with all available columns
            if (strcasecmp(column, "Location")==0 && rows[i].location[0]!='\0' ||
                strcasecmp(column, "City")==0 && rows[i].city[0]!='\0' ||
                strcasecmp(column, "Type")==0 && rows[i].type[0]!='\0' ||
                strcasecmp(column, "Furnish")==0 && rows[i].furnish[0]!='\0' ||
                strcasecmp(column, "Price")==0 && rows[i].price!=0 ||
                strcasecmp(column, "Carparks")==0 && rows[i].carparks!=0 ||
                strcasecmp(column, "Bathrooms")==0 && rows[i].bathrooms!=0 ||
                strcasecmp(column, "Rooms")==0 && rows[i].rooms!=0)
            {
                columnFound = 1; // Implements that the inputted column matched.
                break;
            }
        }

        // Check if the specified column exists in the header
            // If the specified column is found in the header
            if(columnFound)
                break; // Exit the loop if the column is found

            // If the specified column is not found in the header
            else
            {
                printf("\nColumn not found. Please input a valid column!\n"); // Handle invalid input
                PressAnyKey(); // Call function to wait for a key press
                ClearScreen(); // Call function to clear screen

                // Re-display everything after selecting menu 2
                menu();
                printf("Your choice: %d\n", choice);
            }
    }
    while(1); // Continue looping until a valid column is inputted

    // Prompt user for input section
    do
    {
        printf("What data do you want to find? "); // Prompt user to input what to find
        fgets(queryvalue, SIZE, stdin); // Read the entire line

        // Remove the newline character
        size_t len = strlen(queryvalue);
        if(len>0 && queryvalue[len-1] == '\n')
            queryvalue[len-1] = '\0';

        int dataFound = 0; // Counter to track the number of matching rows

        // Loop through the file to find and display matching rows
        for (int i=0; i<totalRows; ++i)
        {
            int isMatch = 0; // Flag to check if the row matches the search criteria

            // Compare the specified column with the query value for fields with STRING INPUT
            if (strcasecmp(column, "Location")==0 && strcasestr(rows[i].location, queryvalue)!=NULL ||
                strcasecmp(column, "City")==0 && strcasestr(rows[i].city, queryvalue)!=NULL ||
                strcasecmp(column, "Type")==0 && strcasestr(rows[i].type, queryvalue)!=NULL ||
                strcasecmp(column, "Furnish")==0 && strcasestr(rows[i].furnish, queryvalue)!=NULL)
            {
                isMatch = 1; // Set isMatch to 1 to indicate matches
            }

            // Compare the specified column with the query value for fields with NUMBER INPUT
            else if ((strcasecmp(column, "Price") == 0 && rows[i].price == strtoull(queryvalue, NULL, 10)) ||
                     (strcasecmp(column, "Rooms") == 0 && rows[i].rooms == strtoul(queryvalue, NULL, 10)) ||
                     (strcasecmp(column, "Bathrooms") == 0 && rows[i].bathrooms == strtoul(queryvalue, NULL, 10)) ||
                     (strcasecmp(column, "Carparks") == 0 && rows[i].carparks == strtoul(queryvalue, NULL, 10)))
            {
                isMatch = 1; // Set isMatch to 1 to indicate matches
            }

            // Print the data when the data searched exists in the column inputted
            if(isMatch)
            {
                // If this is the first matching row, print the header
                if(!dataFound)
                {
                    printf("\nData found. Detail of data:\n");
                    printf("%-30s%-16s%-15s%-12s%-12s%-12s%-12s%-s\n", "Location", "City", "Price", "Rooms", "Bathrooms", "Carparks", "Type", "Furnish");
                }

                // Print the matching data
                printf("%-30s%-16s%-15llu%-12u%-12u%-12u%-12s%-s\n", rows[i].location, rows[i].city, rows[i].price,
                       rows[i].rooms, rows[i].bathrooms, rows[i].carparks, rows[i].type, rows[i].furnish);

                dataFound++; // Increment the counter to track the number of matching rows found
            }
        }

        printf("Total data: %d\n", dataFound); // Print total data found

        // Check if no matching data was found based on the user's query.
            // If true, print a message indicating that the data was not found.
            if(!dataFound)
            {
                printf("\nData not found!\n"); // Handle the error
                PressAnyKey(); // Wait for a key press
                ClearScreen(); // Call function to clear the screen

                // Re-display everything after selecting menu 2
                menu();
                printf("Your choice: %d\n", choice);
                printf("Choose column: %s\n", column);
            }

            // If false, exiting the function
            else
                break; // Stop loop
    }
    while(1); // Continue looping until a valid column is inputted
}

// Comparator function for qsort - Location
int compareLocation(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;
    return strcasecmp(dataA->location, dataB->location);
}

// Comparator function for qsort - City
int compareCity(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;
    return strcasecmp(dataA->city, dataB->city);
}

// Comparator function for qsort - Price
int comparePrice(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;

    // Compare based on the "Price" column
    if(dataA->price < dataB->price)
        return -1;
    else if (dataA->price > dataB->price)
        return 1;
    else
        return 0;
}

// Comparator function for qsort - Rooms
int compareRooms(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;

    // Compare based on the "Rooms" column
    if(dataA->rooms < dataB->rooms)
        return -1;
    else if(dataA->rooms > dataB->rooms)
        return 1;
    else
        return 0;
}

// Comparator function for qsort - Bathrooms
int compareBathrooms(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;

    // Compare based on the "Bathrooms" column
    if (dataA->bathrooms < dataB->bathrooms) return -1;
    else if (dataA->bathrooms > dataB->bathrooms) return 1;
    else return 0;
}

// Comparator function for qsort - Carparks
int compareCarparks(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;

    // Compare based on the "Carparks" column
    if (dataA->carparks < dataB->carparks) return -1;
    else if (dataA->carparks > dataB->carparks) return 1;
    else return 0;
}

// Comparator function for qsort - Type
int compareType(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;
    return strcasecmp(dataA->type, dataB->type);
}

// Comparator function for qsort - Furnish
int compareFurnish(const void *a, const void *b)
{
    data *dataA = (data *)a;
    data *dataB = (data *)b;
    return strcasecmp(dataA->furnish, dataB->furnish);
}

// Function to sort data by ascending/descending
void SortBy(int choice, data* rows, int totalRows) // 219 lines
{
    char column[SIZE], sortvalue[SIZE]; // Declare variables to store user input

    // Prompt user for input section
    do
    {
        printf("Choose column: "); // Prompt user to choose column
        scanf("%s", column); // Read the column choice from the user
        while(getchar()!='\n'); // Clear the input buffer

        // Check if the specified column exists in the header
        int columnFound = 0;
        for(int i=0; i<totalRows; ++i)
        {
            // Compare the chosen column with all available columns
            if(strcasecmp(column, "Location")==0 && rows[i].location[0]!='\0' ||
               strcasecmp(column, "City")==0 && rows[i].city[0]!='\0' ||
               strcasecmp(column, "Type")==0 && rows[i].type[0]!='\0' ||
               strcasecmp(column, "Furnish")==0 && rows[i].furnish[0]!='\0' ||
               strcasecmp(column, "Price")==0 && rows[i].price!=0 ||
               strcasecmp(column, "Carparks")==0 && rows[i].carparks!=0 ||
               strcasecmp(column, "Bathrooms")==0 && rows[i].bathrooms!=0 ||
               strcasecmp(column, "Rooms")==0 && rows[i].rooms!=0)
            {
                columnFound = 1;
                break;
            }
        }

        // Check if the specified column exists in the header
            // If the specified column is found in the header
            if(columnFound)
                break; // Exit the loop if the column is found

            // If the specified column is not found in the header
            else
            {
                printf("\nColumn not found. Please input a valid column!\n"); // Handle invalid input
                PressAnyKey(); // Call function to wait for a key press
                ClearScreen(); // Call function to clear screen

                // Re-display everything after selecting menu 2
                menu();
                printf("Your choice: %d\n", choice);
            }
    }
    while(1); // Continue looping until a valid column is inputted

    int validInput = 0; // Declare a variable to act whether sort option is valid or not

    // Prompt user for input section
    do
    {
        printf("Sort ascending or descending? "); // Prompt user to input what to find
        scanf("%s", sortvalue); // Read the sort order from user
        while(getchar()!='\n'); // Clear the input buffer

        // Sort the data using qsort
          // ASC and DESC have the same back substring "CENDING", thefore the costum function strcasestr not gonna work
            // Ascending
            if(strcasecmp(sortvalue, "Asc")==0 || strcasecmp(sortvalue, "Ascend")==0 || strcasecmp(sortvalue, "Ascending")==0)
            {
                validInput = 1;
                if(strcasecmp(column, "Location")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareLocation);
                }
                else if(strcasecmp(column, "City")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareCity);
                }
                else if(strcasecmp(column, "Price")==0)
                {
                    qsort(rows, totalRows, sizeof(data), comparePrice);
                }
                else if(strcasecmp(column, "Rooms")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareRooms);
                }
                else if(strcasecmp(column, "Bathrooms")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareBathrooms);
                }
                else if(strcasecmp(column, "Carparks")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareCarparks);
                }
                else if(strcasecmp(column, "Type")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareType);
                }
                else if(strcasecmp(column, "Furnish")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareFurnish);
                }
            }

            // Descending
            else if(strcasecmp(sortvalue, "Dsc")==0 || strcasecmp(sortvalue, "Desc")==0 || strcasecmp(sortvalue, "Descend")==0 || strcasecmp(sortvalue, "Descending")==0)
            {
                validInput = 1;
                if(strcasecmp(column, "Location")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareLocation);

                    // Reverse the array
                    for(int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
                else if(strcasecmp(column, "City")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareCity);
                    // Reverse the array
                    for (int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
                else if(strcasecmp(column, "Price")==0)
                {
                    qsort(rows, totalRows, sizeof(data), comparePrice);
                    // Reverse the array
                    for (int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
                else if(strcasecmp(column, "Rooms")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareRooms);
                    // Reverse the array
                    for (int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
                else if(strcasecmp(column, "Bathrooms")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareBathrooms);
                    // Reverse the array
                    for (int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
                else if(strcasecmp(column, "Carparks")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareCarparks);
                    // Reverse the array
                    for (int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
                else if(strcasecmp(column, "Type")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareType);
                    // Reverse the array
                    for (int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
                else if(strcasecmp(column, "Furnish")==0)
                {
                    qsort(rows, totalRows, sizeof(data), compareFurnish);
                    // Reverse the array
                    for (int i=0; i<totalRows/2; i++)
                    {
                        data temp = rows[i];
                        rows[i] = rows[totalRows-i-1];
                        rows[totalRows-i-1] = temp;
                    }
                }
            }

            // Input that are not Ascending or Descending
            else
            {
                printf("\nIncorrect! Please input a valid sorting order!\n"); // Handle invalid input
                PressAnyKey(); // Call function to wait for a key press
                validInput = 0;
                ClearScreen(); // Call function to clear screen

                // Re-display everything after selecting menu 2
                menu();
                printf("Your choice: %d\n", choice);
                continue;
            }

        // Print the header
        printf("\nData found. Detail of data:\n");
        printf("%-30s%-16s%-15s%-12s%-12s%-12s%-12s%-s\n", "Location", "City", "Price", "Rooms", "Bathrooms", "Carparks", "Type", "Furnish");

        // Print the data
        for (int i=0; i<totalRows; i++)
        {
            printf("%-30s%-16s%-15llu%-12u%-12u%-12u%-12s%-s\n", rows[i].location, rows[i].city, rows[i].price,
                   rows[i].rooms, rows[i].bathrooms, rows[i].carparks, rows[i].type, rows[i].furnish);
        }
    }
    while(!validInput); // Continue looping until a valid input is received
}

// Function to  export data to a CSV file
void Export(data* rows, int totalRows) // 41 lines
{
    char filename[SIZE]; // Declare a variable to store the filename

    printf("File name: "); // Prompt user to name the file
    scanf("%s", filename); // Read the filename choice from the user
    while(getchar() != '\n'); // Clear the input buffer

    FILE *file;

    char newFilename[SIZE]; // Declare a temporary filename

    // Find the position of the last dot in the filename
    char *dot = strrchr(filename, '.');

    if(dot!=NULL && dot!=filename)
    {
        file = fopen(filename, "w"); // Open the file with the specified extension
        snprintf(newFilename, sizeof(newFilename), "%s", filename);
    }
    else
    {
        // Append ".csv" if no extension or the dot is the first character
        snprintf(newFilename, sizeof(newFilename), "%s.csv", filename);
        file = fopen(newFilename, "w"); // Open as a CSV file
    }

    // Print the header line
    fprintf(file, "Location, City, Price, Rooms, Bathrooms, Carparks, Type, Furnish\n");

    // Copy sorted data to the new file
    for (int i=0; i<totalRows; ++i)
    {
        fprintf(file, "%s, %s, %llu, %u, %u, %u, %s, %s\n", rows[i].location, rows[i].city,
                rows[i].price, rows[i].rooms, rows[i].bathrooms, rows[i].carparks,
                rows[i].type, rows[i].furnish);
    }

    fclose(file);

    printf("\nData successfully written to file %s!\n", newFilename);
}

// Entry point of the program (Driver Part)
int main() // 78 lines
{
    FILE* file = fopen("file.csv", "r"); // Open the file and get the FILE pointer

     // Check if the file opening was unsuccessful (file pointer is NULL)
    if(file==NULL)
    {
        printf("\nError opening file.csv\n"); // Print an error message to the console
        exit(1); // Terminate the program with an error code
    }

    int totalRows = 0; // Declare variable number of rows in the file

    // Read the total number of rows in the file
    while(fscanf(file, "%*[^\n]"), fscanf(file, "%*c"), !feof(file))
        totalRows++;

    fseek(file, 0, SEEK_SET); // Reset the file pointer to the beginning of the file

    data* rows = (data*)malloc(totalRows * sizeof(data)); // Allocate memory for an array of structs to hold the data

    // Skip the header line
    fscanf(file, "%*[^\n]"); fscanf(file, "%*c");

    // Read and store data in the array of structs
    for(int i=0; i<totalRows; ++i)
    {
        fscanf(file, "%[^,],%[^,],%llu,%u,%u,%u,%[^,],%[^\n]\n", rows[i].location, rows[i].city, &rows[i].price,
               &rows[i].rooms, &rows[i].bathrooms, &rows[i].carparks, rows[i].type, rows[i].furnish);
    }

    fclose(file); // Close the file

    int choice; // Declare a variable to store the choice of the number from the menu

    // Initiate the do-while loop until condition fulfilled
    do
    {
        menu(); // Process to call the menu function

        printf("Your choice: "); // Prompt the user to input a choice
        scanf("%d", &choice); // Scan the number of choice
        while(getchar()!='\n');

        // Process the user's choice
        switch(choice)
        {
            // If the user input is 1, process Display Data function
            case 1:
                DisplayData(choice, rows, totalRows); // Call the DisplayData function
                break; // End of case
            // If the user input is 2, process Select Row function
            case 2:
                SelectRow(choice, rows, totalRows); // Call the SelectRow function
                break; // End of case
            // If the user input is 3, process Sort function
            case 3:
                SortBy(choice, rows, totalRows);// Call the SortBy function
                break;
            // If the user input is 4, process Export function
            case 4:
                Export(rows, totalRows);
                break;
            // If the user input is 5, exit the program
            case 5:
                exit(0); // Terminate program
                break; // End of case
            // If the user input is not between 1 and 5, print error and ask the user to re-input
            default:
                puts("\nError! Please input a valid choice!");
        }
        PressAnyKey(); // Call function to wait for a key press
        ClearScreen(); // Call function to clear screen
    }
    while(choice!=5); // Prompt user for choices from the menu until input 5 is received

    fclose(file); // Close file if finished
    return 0; // Indicates the program successfully executed
}
