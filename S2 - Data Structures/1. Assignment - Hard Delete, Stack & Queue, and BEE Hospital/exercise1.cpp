// Use Double Linked List
// Reason: Allows bidirectional traversal, easier removing elements or iterating backwards through the list.
// More versatile and efficient when dealing with operations that require traversal in both directions.

#include <stdio.h> // Header file for standard input-output operations
#include <stdlib.h> //Header file for standard library functions such as memory allocation and deallocation
#include <string.h> // Header file for string manipulation functions

// Class to store contact variables related
struct Contact
{
    char name[102], mobileNumber[17];
    struct Contact *prev; // Pointer to the previous contact in the linked list
    struct Contact *next; // Pointer to the next contact in the linked list
} *head, *tail, *curr; // Head: Start node | Curr: Moving node | Tail: End node

// Function to create a new contact with the given name and mobile number
struct Contact* createContact(char name[], char mobileNumber[])
{
    struct Contact *newContact = (struct Contact*)malloc(sizeof(struct Contact)); // Allocate memory for the new contact

    // Copy the name and mobile number to the new contact
    strcpy(newContact->name, name); strcpy(newContact->mobileNumber, mobileNumber);

    newContact->next = NULL; // Set the next pointer of the new contact to NULL
    return newContact; // Return the pointer to the new contact
}

// The separation of the struct allows for better modularity and encapsulation of functionality

void printMenu()
{
    printf("\n[PROGRAM MENU]\n");
    printf("1. Create New Contact\n");
    printf("2. Remove Contacts\n");
    printf("3. Exit Program\n");
    printf("Insert your input: ");
}

void addContact(char name[], char mobileNumber[]) // Pushback
{
    struct Contact *newContact = createContact(name, mobileNumber);

    if(head == NULL) // If the list is empty
    {
        head = tail = newContact;
        head->prev = NULL;
        tail->next = NULL;
    }

    else // Otherwise
    {
        newContact->next = NULL;
        tail->next = newContact;
        newContact->prev = tail;
        tail = newContact;
    }
}

void removeContacts(char str[])
{
	if(head == NULL) // If the Linked List is empty
    {
		printf("\nThe Linked List is empty!\n");
		return;
	}

    struct Contact *prev = NULL;
    curr = head;
    int nodesRemoved = 0; // Variable to store the number of nodes removed

    while(curr != NULL)
    {
        // Check if the name contains the inputted string (case-insensitive)
        if(strstr(curr->name, str) != NULL || strcasecmp(curr->name, str) == 0)
        {
            if(prev == NULL) // If the node is the first node
            {
                head = curr->next;

                if(head != NULL)
                {
                    head->prev = NULL;
                }

                else
                {
                    tail = NULL; // If the only node was removed
                }

                free(curr);
                curr = head;
            }

            else // Otherwise
            {
                prev->next = curr->next;

                if(curr == tail)
                {
                    tail = prev;
                }

                else
                {
                    curr->next->prev = prev;
                }

                struct Contact *temp = curr;
                curr = curr->next;
                free(temp);
            }

            nodesRemoved++; // Increment the count of nodes removed
        }

        else // Move to the next node
        {
            prev = curr;
            curr = curr->next;
        }
    }

    // Print the number of nodes removed
    if(nodesRemoved<=0)
    {
        printf("No nodes are deleted!\n");
    }

    else if(nodesRemoved==1)
    {
        printf("%d node is deleted!\n", nodesRemoved);
    }

    else
    {
        printf("%d nodes are deleted!\n", nodesRemoved);
    }
}

void displayContacts()
{
    printf("[DATA IN THE LINKED LIST]\n");
    int count = 1;
    curr = head;

    while(curr != NULL) // Traverse the linked list and print each contact
    {
        printf("%d. %s - %s\n", count++, curr->name, curr->mobileNumber);
        curr = curr->next;
    }
}

void freeList()
{
    struct Contact *temp;
    struct Contact *curr = head;

    while(curr != NULL)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}

// Main driver
int main()
{
    int choice = 0; // Variable to store user menu choice
    struct Contact contactList; // Temporary contact variable for user input

    head = tail = curr = NULL; // Initialize head, tail, and curr pointers to NULL

    // Add initiated contacts
    addContact("Budi", "0812345678");
    addContact("Bayu", "0812345678");
    addContact("Erwin", "0812345678");
    addContact("Budi", "0812345678");
    addContact("Yakob", "0812345678");
    addContact("Fredy", "0812345678");
    addContact("Budi", "0812345678");

    do // Menu-driven loop to interact with the program
    {
        displayContacts(); printMenu();

        // if(isDigit)
        if(scanf("%d", &choice) != 1) // To make sure the input is a number
        {
            printf("\nInvalid input! Please enter the number of choice.\n\n");
            while(getchar() != '\n'); // Clear input buffer
                continue;
        }

        switch(choice)
        {
            case 1: // Prompt user for contact information
                printf("Input name of the contact: "); scanf("%s", contactList.name);
                printf("Input phone number of the contact: "); scanf("%s", contactList.mobileNumber);

                addContact(contactList.name, contactList.mobileNumber); // Add new contact to the linked list
                break;

            case 2: // Prompt user for contact to remove by name
                printf("Input the name of the contact: "); scanf("%s", contactList.name);

                removeContacts(contactList.name);
                break;

            case 3: // Exit
                printf("Exiting program...\n");
                break;

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 3.\n");
        }
        printf("\n");
    }
    while(choice != 3); // Continue loop until user chooses to exit

    freeList(); // Free the memory allocated for contacts

    return (0);
}
