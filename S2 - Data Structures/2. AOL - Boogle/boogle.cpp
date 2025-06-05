#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define SIZE 128

// Function to clear the input buffer
void ClearBuffer()
{
    while(getchar() != '\n');
}

// Function to wait for Enter key press
void PressEnter()
{
    printf("Press ENTER to continue..."); getchar();
}

// Function to clear the screen
void ClearScreen()
{
    #if defined(_WIN32) || defined(_WIN64) // Windows
        system("CLS");
    #else // Unix-like systems
        system("CLEAR");
    #endif
}

// Function to check input validity
int checkInput(char* input, int min_length, int is_word)
{
    int len = strlen(input);

    if(len <= min_length) // Check if input length is less than minimum required length
    {
        return 0;
    }

    if(is_word) // Check if input consists of alphabetic characters only
    {
        for(int i = 0; i < len; i++)
        {
            if(!isalpha(input[i]))
            {
                return 0;
            }
        }
    }

    else // Check if input has more than the required number of words
    {
        int word_count = 1;

        for(int i = 0; i < len; i++)
        {
            if(input[i] == ' ')
            {
                word_count++;
            }
        }

        if(word_count < min_length)
        {
            return 0;
        }
    }

    return 1;
}

// Function to display the menu options
void Menu()
{
    puts("+-------------------------------------+");
    puts("|              B O O G L E            |");
    puts("+-------------------------------------+");
    puts("| 1. Release a slang word             |");
    puts("| 2. Search a slang word              |");
    puts("| 3. View all slang words with prefix |");
    puts("| 4. View all slang words             |");
    puts("| 5. Exit                             |");
    puts("+-------------------------------------+");
    printf(">> ");
}

// Trie node structure
typedef struct TrieNode
{
    char word;
    char* description;
    struct TrieNode* children[26];
} TrieNode;

// Function to create a new Trie node
TrieNode* createTrieNode(char word)
{
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->word = word;

    for(int i = 0; i < 26; i++)
    {
        node->children[i] = NULL;
    }

    node->description = NULL;

    return node;
}

// Function to insert a new slang word into the Trie
void insertTrie(TrieNode* root, char* word, char* description)
{
    TrieNode* current = root;

    for(int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';

        if(current->children[index] == NULL)
        {
            current->children[index] = createTrieNode(word[i]);
        }
        current = current->children[index];
    }

    if(current->description!= NULL)
    {
        free(current->description);
    }

    current->description = strdup(description);
}

// Function to search for a slang word in the Trie
char* searchTrie(TrieNode* root, char* word)
{
    TrieNode* current = root;

    for(int i = 0; i < strlen(word); i++)
    {
        int index = word[i] - 'a';

        if(current->children[index] == NULL)
        {
            return NULL;
        }
        current = current->children[index];
    }

    return current->description;
}

// Recursive function to print words starting with a given prefix
void printPrefixWords(TrieNode* node, char* prefix, int* count)
{
    if(node->description != NULL) // If the current node is the end of a word, print it
    {
        printf("%d. %s\n", ++(*count), prefix);
    }

    for(int i = 0; i < 26; i++) // Recursively traverse all child nodes
    {
        if(node->children[i] != NULL)
        {
            char newPrefix[SIZE];
            sprintf(newPrefix, "%s%c", prefix, 'a' + i);
            printPrefixWords(node->children[i], newPrefix, count);
        }
    }
}

// Recursive function to print all words in the Trie
void printAllWords(TrieNode* root, char* prefix, int* count)
{
    if(root->description != NULL) // If the current node is the end of a word, print it
    {
        printf("%d. %s\n", ++(*count), prefix);
    }

    for(int i = 0; i < 26; i++) // Recursively traverse all child nodes
    {
        if(root->children[i] != NULL)
        {
            char newPrefix[SIZE];
            sprintf(newPrefix, "%s%c", prefix, 'a' + i);
            printAllWords(root->children[i], newPrefix, count);
        }
    }
}

// Entry point of the program
int main()
{
    int choices, totalSlang = 0;
    TrieNode* root = createTrieNode('\0'); // Create root node of Trie

    do // Main loop for menu selection
    {
        ClearScreen(); Menu();
        if(scanf("%d", &choices) != 1 || choices < 1 || choices > 5)
        {
            printf("\nInvalid choice. Please input between 1 and 5.\n");
            ClearBuffer(); PressEnter();
        }

        else
        {
            ClearBuffer(); printf("\n");
        }

        switch(choices) // Switch based on user choice
        {
            case 1: // Release a new slang word
            {
                char slang_word[SIZE], slang_desc[SIZE];

                do
                {
                    printf("Input a new slang word [Must be more than 1 character and contains no space]: ");
                    scanf("%s", slang_word); ClearBuffer();
                }
                while(!checkInput(slang_word, 1, 1));

                do
                {
                    printf("Input a new slang word description [Must be more than 2 words]: ");
                    fgets(slang_desc, SIZE, stdin);
                }
                while(!checkInput(slang_desc, 3, 0));

                insertTrie(root, slang_word, slang_desc); totalSlang++;
                puts("\nSuccessfully released new slang word.");

                PressEnter(); break;
            }

            case 2: // Search for a slang word
            {
                char slang_search[SIZE];

                do
                {
                    printf("Input a slang word to be searched [Must be more than 1 character and contains no space]: ");
                    scanf("%s", slang_search); ClearBuffer();
                }
                while(!checkInput(slang_search, 1, 1));

                if(searchTrie(root, slang_search) != NULL)
                {
                    printf("\nSlang word : %s\n", slang_search);
                    printf("Description: %s\n", searchTrie(root, slang_search));
                }

                else
                {
                    printf("\nThere is no word \"%s\" in the dictionary.\n", slang_search);
                }

                PressEnter(); break;
            }

            case 3: // View all slang words starting with a prefix
            {
                TrieNode* current = root;
                int count = 0, i;
                char prefix[SIZE];

                printf("Input a prefix to search: ");
                scanf("%s", prefix); ClearBuffer();

                for(i = 0; prefix[i] != '\0'; i++)
                {
                    int index = prefix[i] - 'a';

                    if(current->children[index] == NULL)
                    {
                        printf("\nThere is no prefix '%s' in the dictionary.\n", prefix);
                        PressEnter(); break;
                    }

                    current = current->children[index];
                }

                if(prefix[i] == '\0') // If the loop completed without a break
                {
                    printf("\nWords starting with prefix '%s':\n\n", prefix);
                    printPrefixWords(current, prefix, &count);
                    printf("\n"); PressEnter();
                }

                break;
            }

            case 4: // View all slang words in the dictionary
            {
                int count = 0;

                if(totalSlang == 0)
                {
                    printf("There is no slang word yet in the dictionary.\n");
                }

                else
                {
                    printf("List of all slang words in the dictionary:\n");

                    if(root != NULL)
                    {
                        printAllWords(root, "", &count);
                    }
                }

                printf("\n"); PressEnter(); break;
            }

            case 5:
            {
                free(root); // Free allocated memory
                printf("Thank you... Have a nice day :)"); // Print exit message
                break;
            }
        }
    }
    while(choices!=5); // Repeat until 5 (Exit) is inputted

    return 0;
}
