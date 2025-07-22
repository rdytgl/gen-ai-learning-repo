// This code computes for the approximate grade level readability using the Coleman-Liau index
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_sentences(string text);
int count_words(string text);
int count_letters(string text);

int main(void)
{
    // Gets the user's input for computation of the index
    string txt = get_string("Text: ");

    int sentence_count = count_sentences(txt);
    // printf("Total Sentence Length: %f\n", sentence_count);
    int word_count = count_words(txt);
    // printf("Total Word Count: %f\n", word_count);
    int letter_count = count_letters(txt);
    // printf("Total Letter Length: %f\n", letter_count);

    if (word_count == 0)
    {
        printf("Warning! No word was entered\n");
    }

    // Computes for the index
    double L = ((double) letter_count / word_count) * 100; // Computes the value of L
    // printf("L: %f\n", L);
    double S = ((double) sentence_count / word_count) * 100; // Computes the value of S
    // printf("S: %f\n", S);
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int index_rounded = round(index);

    // Prints the results
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index_rounded);
    }
}

int count_sentences(string text)
{
    // Gets the number of sentences of each text
    int sentence_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '?' || text[i] == '.' || text[i] == '!')
        {
            sentence_count++;
        }
    }

    return sentence_count;
}

int count_words(string text)
{
    int word_count = 0;
    bool in_word = false;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
        {
            word_count++;
        }
    }
    return word_count + 1;
}

int count_letters(string text)
{
    // Gets the number of words in each text
    int letter_count = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter_count++;
        }
    }
    return letter_count;
}
