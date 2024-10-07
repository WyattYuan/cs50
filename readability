#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_sentences(string text);
int count_words(string text);

int main(void)
{
    // get input
    string text = get_string("Text: ");

    // count letters
    int letters = count_letters(text);

    // count words,sentences
    int sentences = count_sentences(text);
    int words = count_words(text);

    // compute index
    double L = letters / (words / 100.0);
    double S = sentences / (words / 100.0);
    double index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = (int) round(index);

    // print out
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {

        printf("Grade %d\n", grade);
    }
}

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}
int count_words(string text)
{
    int words = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) && (ispunct(text[i + 1]) || isspace(text[i + 1])) &&
            text[i + 1] != '-' && text[i + 1] != '\'')
        {
            words++;
        }
    }
    return words;
}
