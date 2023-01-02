// Libraries
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // String with the user input
    string name = get_string("Whats your name? ");

    // Printing the message with "name", the variable that constains the user input
    printf("Hello, %s\n", name);
}