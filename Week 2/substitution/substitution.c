#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Declare functions
bool check_key(string key);
char *get_ciphertext(char *new_alphabet, string text);


// Declare constant variables
const int ALPHABET_LENGTH = 26;


int main(int argc, string argv[])
{
    // Check if the argument with the key is valid
    if (argv[1] == NULL || argv[2] != NULL)
    {
        printf("Please insert only one key with 26 chars\n");
        return 1;
    }


    // Check if the key is valid
    const string key = argv[1];
    if (!check_key(key))
    {
        printf("The key must contain 26 characters\n");
        return 1;
    }


    // Make the new alphabet with the key characters
    char new_alphabet[ALPHABET_LENGTH];
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        new_alphabet[i] = key[i];
    }


    // Get uset input
    string text = get_string("plaintext: ");


    // Print ciphertext output
    printf("ciphertext: %s\n", get_ciphertext(new_alphabet, text));
}



char *get_ciphertext(char *new_alphabet, string text)
{
    int l = strlen(text);
    char *new_text = malloc(l + 1);
    for (int i = 0; i < l; i++)
    {
        char actual_letter = text[i];
        if (isalpha(actual_letter))
        {
            if (islower(actual_letter))
            {
                char new_letter = new_alphabet[(int) actual_letter - 97];
                new_text[i] = tolower(new_letter);
            }
            else
            {
                char new_letter = new_alphabet[(int) actual_letter - 65];
                new_text[i] = toupper(new_letter);
            }
        }
        else
        {
            new_text[i] = actual_letter;
        }
    }

    return new_text;
}


bool check_key(string key)
{
    if (strlen(key) != ALPHABET_LENGTH)
    {
        return false;
    }

    static char actual_letters[ALPHABET_LENGTH];
    for (int i = 0; i < ALPHABET_LENGTH; i++)
    {
        // Chech if the character is not alphanumeric
        if (!isalpha(key[i]))
        {
            return false;
        }

        // Check if the character is twice in the key
        if (strchr(actual_letters, key[i]) != NULL)
        {
            return false;
        }
        actual_letters[i] = key[i];
    }

    return true;
}