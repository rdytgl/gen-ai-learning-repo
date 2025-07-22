// This code is made to compare the scores of the two words entered by each player
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int CHAR_SCORE[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int word_score(string word);

int main(void)
{
    // Gets the word for each player and stores it in
    string player1_word = get_string("Player 1: ");
    string player2_word = get_string("Player 2: ");

    // Gets the total score of each words
    int player1_score = word_score(player1_word);
    int player2_score = word_score(player2_word);

    // Prints the result
    if (player1_score > player2_score)
    {
        printf("Player 1 wins!\n");
    }
    else if (player2_score > player1_score)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int word_score(string word)
{
    int score = 0;
    int n = strlen(word);

    for (int i = 0; i < n; i++)
    {
        if (isupper(word[i]))
        {
            score += CHAR_SCORE[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += CHAR_SCORE[word[i] - 'a'];
        }
        else
        {
            score += 0;
        }
    }
    return score;
}
