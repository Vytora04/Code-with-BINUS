#include <stdio.h> // Header file for standard input-output operations
#include <stdlib.h> //Header file for standard library functions such as memory allocation and deallocation
#include <string.h> // Header file for string manipulation functions

// Class to store hospital data variables related
struct data
{
	int membershipTypeInt;
	int queueNumber;
	char membershipType[10];
	char name[31];

	struct data *next; // Pointer to the previous contact in the linked list
	struct data *prev; // Pointer to the next contact in the linked list
}*head, *tail, *curr; // Head: Start node | Curr: Moving node | Tail: End node

void pushSorted(char membershipType[], int *queueNumber, char name[])
{
	struct data *newNode = (struct data*) malloc(sizeof(struct data)); // Allocate memory for the patient

	// Copy the name and membership type to the queue
	strcpy(newNode->membershipType, membershipType);
 	strcmp(membershipType,"VIP") == 0 ? newNode->membershipTypeInt = 1 : newNode->membershipTypeInt = 2; 	// 1 = VIP, 2 = Regular
	newNode->queueNumber = *queueNumber;
	strcpy(newNode->name, name);

	// Set the pointer to NULL
    newNode->next = NULL;
	newNode->prev = NULL;

	if(head == NULL) // If the queue is empty, insert newNode as the first node
    {
		head = tail = newNode;
	}

	else // Otherwise
	{
		struct data *temp = head;

		// Traverse the queue to find the correct position for insertion
		while(temp != NULL && newNode->membershipTypeInt > temp->membershipTypeInt)
        {
			temp = temp->next;
		}

		if(temp == head) // Insert newNode at the beginning if it has higher priority than the current head
        {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}

		else if(temp == NULL) // Insert newNode at the end if it has lower priority than the current tail
        {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}

		else // Insert newNode in between if it has higher priority than some nodes but lower than others
        {
			newNode->prev = temp->prev;
			newNode->next = temp;
			temp->prev->next = newNode;
			temp->prev = newNode;
		}
	}

	// Print and increment
	printf("! Added %s [NO:%d][%s]\n", newNode->name, newNode->queueNumber, newNode->membershipType);
	(*queueNumber)++;
}

// Function to removes and prints the first patient's information from the queue, or prints a message if the queue is empty
void popData()
{
    if(head == NULL) // If there is no data
    {
        printf("! The queue is empty!\n");
    }

    else if(head == tail) // If there is only one data
    {
        struct data *temp = head;
        printf("! Removed %s [NO:%d][%s]\n", temp->name, temp->queueNumber, temp->membershipType);
        head = tail = NULL;
        free(temp);
    }

    else // If there is more than one data
    {
        struct data *temp = head;
        printf("! Removed %s [NO:%d][%s]\n", temp->name, temp->queueNumber, temp->membershipType);
        head = head->next;
        head->prev = NULL;
        free(temp);
    }
}

void clearData()
{
    while(head != NULL)
    {
		struct data *temp = head;
		printf("! Removed %s [NO:%d][%s]\n", temp->name, temp->queueNumber, temp->membershipType);
		head = head->next;
		free(temp);
	}
}

// Main driver
int main()
{
    int input;
    int queueNumber = 1;
	char membershipType[10];
	char name[31];

	do // Menu-driven loop to interact with the program
    {
        // if(isDigit)
        if(scanf("%d", &input) != 1) // To make sure the input is a number
        {
            while(getchar() != '\n'); // Clear input buffer
                continue;
        }

		switch(input)
		{
			case 1: // Add patient data
                scanf("%s %[^\n]", &membershipType, &name);
                pushSorted(membershipType, &queueNumber, name);

                break;

			case 2: // Delete a patient
                popData();

                break;

            case 3: // Exit and clear all data
                clearData();
                printf("Exiting program...\n");

                break;
		}
	}
	while(input != 3);

	return (0);
}
