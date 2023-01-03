#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

// Declare functions
void print_bulb(char bit);
char *int_to_binary(int number);


int main(void)
{
    // Get user input
    string text = get_string("Text: ");

    // Get the ASCII int for each char in the user input string
    int length = strlen(text);
    int text_in_int[length];
    for (int i = 0; i < length; i++)
    {
        text_in_int[i] = (int) text[i];
    }

    // Convert each ASCII char to binary and print with the print_bulb function to see the emojis
    string binary;
    for (int i = 0; i < length; i++)
    {
        binary = int_to_binary(text[i]);
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(binary[j]);
        }
        printf("\n");
    }
}


char *int_to_binary(int number)
{
    // Declare an array of chars (string) to store the binary representation
    static char binary[BITS_IN_BYTE];

    // Build the binary representation
    int index = 0;
    while (number > 0)
    {
        binary[index] = (number % 2) + '0';
        number /= 2;
        index++;
    }

    // Fill the empty "bits" with ceros because each digit will have 8 bits in this problem (just for the sake of consistensy)
    while (index < BITS_IN_BYTE)
    {
        binary[index] = '0';
        index++;
    }

    // Reverse the string
    int start = 0;
    int end = strlen(binary) - 1;
    char tmp;
    while (start < end)
    {
        tmp = binary[start];
        binary[start] = binary[end];
        binary[end] = tmp;
        start++;
        end--;
    }

    return binary;
}


void print_bulb(char bit)
{
    if (bit == '0')
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == '1')
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}