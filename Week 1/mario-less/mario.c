#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // User input
    int HEIGHT;
    do
    {
        HEIGHT = get_int("How tall do you want the pyramid? ");
    }
    while (HEIGHT > 8 || HEIGHT < 1);


    // for loop to make rows
    for (int i = 1; i <= HEIGHT; i++)
    {
        // for loops to make columns
        for (int j = HEIGHT; j > 0; j--)
        {
            if (i >= j)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}