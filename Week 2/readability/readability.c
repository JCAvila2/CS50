#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



// Declaring functions
int count_letters(string);
int count_words(string);
int count_sentences(string);


int main(void)
{
    // Getting user input
    string text = get_string("Text: ");

    // Counting letters
    int letters = count_letters(text);

    // counting words
    int words = count_words(text);

    // counting sentences
    int sentences = count_sentences(text);


    // Putting it all together
    float L = ((float) letters / (float) words) * 100;
    float S = ((float) sentences / (float) words) * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Rounding index to make it a grade
    int grade = (int) round((double)index);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}


// Functions
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}


int count_words(string text)
{
    int words = 1;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return words;
}



int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}