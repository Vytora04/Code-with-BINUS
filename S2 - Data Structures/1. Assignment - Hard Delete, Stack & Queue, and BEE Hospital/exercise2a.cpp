#include <stdio.h> // Header file for standard input-output operations
#include <stdlib.h> //Header file for standard library functions such as memory allocation and deallocation
#include <string.h> // Header file for string manipulation functions
#define MAX_SIZE 15 // Define a maximum number of elements can hold (up to 15)

// Class to store orders variables related
struct Orders
{
    char order[52];
    struct Orders *prev; // Pointer to the previous contact in the linked list
    struct Orders *next; // Pointer to the next contact in the linked list
} *head, *tail, *curr; // Head: Start node | Curr: Moving node | Tail: End node

void printMenu()
{
	printf("1. Add New Order\n");
	printf("2. Remove Latest Order\n");
	printf("3. Remove All Orders\n");
	printf("4. View Orders\n");
	printf("5. Exit\n");
    printf("Input your choice: ");
}

// Function to adds a new order to the front of the linked list
void pushFront(char name[])
{
    // Allocate memory for a new order
    struct Orders *newOrder = (struct Orders*) malloc(sizeof(struct Orders));
    strcpy(newOrder->order, name); // Copy the name of the order

    if(head == NULL) // If the list is empty, set the new order as both head and tail
    {
        newOrder->next = NULL;
        newOrder->prev = NULL;
        head = tail = newOrder;
    }

    else // Otherwise, insert the new order at the front of the list
    {
        newOrder->next = head;
        head->prev = newOrder;
        head = newOrder;
        head->prev = NULL;
    }
}

void inputOrder()
{
	int len = 0; // Variable to store length of words
    char name[102]; // Buffer to store the name of the order

    // Ask the user to input the name of the order until a valid name is provided
    do
    {
        printf("Input order menu[5..50]: ");
        scanf("%[^\n]", name); getchar();
        len = strlen(name); // Calculate the length of the input
    }
    while(len<5 || len>50); // Repeat until the length is within the specified range

    pushFront(name); // Add the order to the list
}

void clearAll()
{
	while(head != NULL)
    {
		curr = head;
		head = head->next;
		free(curr);
	}
}

// Function to remove latest order
void deleteBack()
{
	printf("\nThe order you are going to remove is %s\n", head->order);

	curr = head;

	if(head == tail)
    {
		free(curr);
		head = tail = NULL;
	}

	else
    {
		head = head->next;
		free(curr);
		head->prev = NULL;
	}
}

void viewItems(int count)
{
    curr = head;

    if(curr == NULL)
    {
        printf("You have no order in the stack!\n");
    }

	else
    {
        printf("\nYour orders in the stack:\n");

        for(int i=1 ; i<=count; i++)
        {
            printf("%d) %s\n", i, curr->order);
            curr = curr->next;
        }
    }
}

// Main Driver
int main()
{
	int choice = 0, count = 0;

	do // Menu-driven loop to interact with the program
    {
		printf("The maximum number of order is %d, the total order that can be added is %d\n", MAX_SIZE, MAX_SIZE-count);
		printMenu();

        // if(isDigit)
        if(scanf("%d", &choice) != 1) // To make sure the input is a number
        {
            printf("\nInvalid input! Please enter the number of choice.\n\n");
            while(getchar() != '\n'); // Clear input buffer
                continue;
        }

		switch(choice)
		{
			case 1: // Add item
                if(count < MAX_SIZE)
                {
                    inputOrder();
                    count++;
                }

                else
                {
                    printf("\nThe stack is at the maximum size!\n");
                }

                break;

			case 2: // Remove latest order
                if(count > 0)
                {
                    deleteBack();
                    count--;
                }

                else
                {
                    printf("\nYou have no order in the stack!\n");
                }

                break;

			case 3: // Remove all orders
                if(count > 0)
                {
                    clearAll();
                    count = 0;
                }

                else
                {
                    printf("\nYou have no order in the stack!\n");
                }

                break;

            case 4: // View order
                if(count > 0)
                {
                    viewItems(count);
                }

                else
                {
                    printf("\nYou have no order in the stack!\n");
                }

                break;

            case 5: // Exit
                printf("Exiting program...\n");
                break;

            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5."); // Display error message for invalid input
		}
		printf("\n");
	}
	while(choice != 5);

	clearAll();

	return (0);
}
