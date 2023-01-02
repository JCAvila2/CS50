#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>


int main(void)
{
    // Declare functions
    long get_user_input(void);
    bool luhn(long);
    int get_len(long);
    int get_digit(long, int);
    int get_last_digit(long);


    // promt user for card number
    const long card_number = get_user_input();


    // if number is valid continue cheking other things
    if (luhn(card_number))
    {
        int len = get_len(card_number);
        int first_digit = get_digit(card_number, 1);
        int second_digit = get_digit(card_number, 2);

        if (len == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7))
        {
            printf("AMEX\n");
        }
        else if (len == 16 && first_digit == 5 && (second_digit == 1 || second_digit == 2 || second_digit == 3 || second_digit == 4
                 || second_digit == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((len == 13 || len == 16) && first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // if number is not valid print invalid
    else
    {
        printf("INVALID\n");
    }
}


// Functions

// Function that return the user input
long get_user_input(void)
{
    return get_long("Insert card number: ");
}


// Function that apply Luhn’s Algorithm
bool luhn(long num)
{
    int sum = 0;
    bool is_second = false;
    while (num > 0)
    {
        int digit = num % 10;
        if (is_second)
        {
            digit = digit * 2;
        }
        sum += digit / 10;
        sum += digit % 10;

        is_second = !is_second;
        num /= 10;
    }
    return sum % 10 == 0;
}


// Function that returns the lenght of the long variable
int get_len(long n)
{
    int len = 0;
    while (n > 0)
    {
        len++;
        n = n / 10;
    }
    return len;
}


// Function that returns the specified digit of the long variable
int get_digit(long n, int p)
{
    int get_len(long);
    int c = get_len(n);
    while (n > 0)
    {
        if (c == p)
        {
            return n % 10;
        }
        c--;
        n /= 10;
    }
    return 0;
}


// Function that returns the last digit of the long variable
int get_last_digit(long number)
{
    return number % 10;
}