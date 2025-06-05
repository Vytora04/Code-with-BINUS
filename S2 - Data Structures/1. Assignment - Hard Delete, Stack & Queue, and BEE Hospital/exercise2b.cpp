#include <stdio.h> // Header file for standard input-output operations
#include <stdlib.h> //Header file for standard library functions such as memory allocation and deallocation
#include <string.h> // Header file for string manipulation functions
#define MAX_SIZE 10 // Define a maximum number of elements can hold (up to 10)

// Class to store items variables related
struct Items
{
    char item[52];
    struct Items *prev; // Pointer to the previous contact in the linked list
    struct Items *next; // Pointer to the next contact in the linked list
} *head, *tail, *curr; // Head: Start node | Curr: Moving node | Tail: End node

void printMenu()
{
	printf("1. Add Item\n");
	printf("2. Purchase Item\n");
	printf("3. Clear Items\n");
	printf("4. View Items\n");
	printf("5. Exit\n");
	printf("Input your choice: ");
}

// Function to adds a new item to the back of the linked list
void pushBack(char name[])
{
    // Allocate memory for a new item
    struct Items *newItem = (struct Items*) malloc(sizeof(struct Items));
    strcpy(newItem->item, name); // Copy the name of the item

    if(head == NULL) // If the list is empty, set the new item as both head and tail
    {
        newItem->next = NULL;
        newItem->prev = NULL;
        head = tail = newItem;
    }

    else // Otherwise, insert the new item at the last of the list
    {
        tail->next = newItem;
		newItem->prev = tail;
		tail = newItem;
		newItem->next = NULL;
    }
}

void inputItem()
{
	int len = 0; // Variable to store length of words
    char name[102]; // Buffer to store the name of the item

    // Ask the user to input the name of the item until a valid name is provided
    do
    {
        printf("Input new item[5..50]: ");
        scanf("%[^\n]", name); getchar();
        len = strlen(name); // Calculate the length of the input
    }
    while(len<5 || len>50); // Repeat until the length is within the specified range

    pushBack(name); // Add the item to the list
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

// Function to purchase earliest item
void deleteFront()
{
	printf("\nThe item you are going to purchase is %s\n", head->item);

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
        printf("You have no item in the queue!\n");
    }

	else
    {
        printf("\nYour items in the queue:\n");

        for(int i=1 ; i<=count; i++)
        {
            printf("%d) %s\n", i, curr->item);
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
		printf("The maximum number of item is %d, the total item that can be added is %d\n", MAX_SIZE, MAX_SIZE-count);
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
                    inputItem();
                    count++;
                }

                else
                {
                    printf("\nThe queue is at the maximum size!\n");
                }

                break;

			case 2: // Purchase item
                if(count > 0)
                {
                    deleteFront();
                    count--;
                }

                else
                {
                    printf("\nYou have no item in the queue!\n");
                }

                break;

			case 3: // Clear item
                if(count > 0)
                {
                    clearAll();
                    count = 0;
                }

                else
                {
                    printf("\nYou have no item in the stack!\n");
                }

                break;

            case 4: // View items
                if(count > 0)
                {
                    viewItems(count);
                }

                else
                {
                    printf("\nYou have no item in the stack!\n");
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
