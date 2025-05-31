#include <stdio.h>
#include <string.h>

// Function to inverse a character case
char inverse_case(char c)
{
    if (c>='A' && c<='Z') // Check if it is uppercase
    {
        return c+32; // Return the character format to lowercase
    }
    else if (c>='a' && c<='z') //Check if it is lowercase
    {
        return c-32; // Return the character format to uppercase
    }
    return c; // Return the result
}

// Function to handle string conversion (without manual reversal)
void string_conversion(char *str)
{
    // Declare a variable to store counted length of string
    int length = strlen(str);

    // Iterate through the string for reversion
    printf("Reversed String: ");
    for (int i=length-1; i>=0; i--)
    {
        printf("%c", str[i]); // Print the current character
    }
    printf("\n"); // Move to the next line after printing the reversed string

    // Iterate through the string for case inversion (without reversing)
    printf("Converted String: ");
    for (int i=0; i<length; i++)
    {
        printf("%c", inverse_case(str[length-i-1])); // Invert the case of each character without re-reversing
    }
    printf("\n"); // Move to the next line after printing converted string
}

// Entry point of the program (Driver Part)
int main()
{
    char S[105]; // Array to hold a string

    printf("Enter a string: "); // Prompt user to input a string
    scanf("%s", S); // Scan the string inputted by the user

    string_conversion(S); // Process to call the string conversion function

    return 0; // Indicate successful program execution
}
