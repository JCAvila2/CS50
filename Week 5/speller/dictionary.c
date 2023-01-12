// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Declare variables
int counter = 0;
int hash_value;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Check in which index should be the word
    hash_value = hash(word);
    node *pointer = table[hash_value];

    // Iterate through the linked list
    while (pointer != NULL)
    {
        // Check if this node contains the word that we are looking for
        if (strcasecmp(pointer -> word, word) == 0)
        {
            return true;
        }

        // else update the pointer to the next node in the linked list
        pointer = pointer -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // This function uses a sum of ASCII values to hash the word, so the first step is declare the initial value for total_sum
    long total_sum = 0;

    // Iterate through each character of the string
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        // Add to the total value
        total_sum += tolower(word[i]);
    }

    // Divide the total value by the number of buckets in the hash table
    return total_sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Dictionary file cannot be opened \n");
        return false;
    }


    // Read each word until the end of the file
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Allocate memory for a new node
        node *node_space = malloc(sizeof(node));
        if (node_space == NULL)
        {
            return false;
        }

        counter++;

        // Copy the word to the new node
        strcpy(node_space -> word, word);

        // Set the pointer to the previous node
        hash_value = hash(word);
        node_space -> next = table[hash_value];
        table[hash_value] = node_space;
    }

    // Close the dictionary file and return true
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return the value of the variable that counts the amount of words in dictionary (variable declared in line 27)
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the table
    for (int i = 0; i < N; i++)
    {
        // Make a pointer pointing at the first node of the linked list in the actual bucket of the hash table
        node *pointer = table[i];

        // Iterate through the linked list
        while (pointer != NULL)
        {
            // Make a temporal pointer pointing to the next node
            node *temp = pointer -> next;

            // Free the actual pointer
            free(pointer);

            // Update the pointer with the temporal pointer
            pointer = temp;
        }
    }
    return true;
}
