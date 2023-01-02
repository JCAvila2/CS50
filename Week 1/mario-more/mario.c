#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // User input
    int HEIGHT;
    do
    {
        HEIGHT = get_int("How tall do you want the pyramids? ");
    }
    while (HEIGHT < 1 || HEIGHT > 8);


    // for loop to make rows
    for (int i = 1; i <= HEIGHT; i++)
    {

        // for loop to make columns on the left pyramid
        for (int l = HEIGHT; l > 0; l--)
        {
            if (i >= l)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        // make separation between pyramids
        printf("  ");

        // for loop to make columns on the right pyramid
        for (int r = 1; r <= HEIGHT; r++)
        {
            if (i >= r)
            {
                printf("#");
            }
        }
        
        printf("\n");
    }
}