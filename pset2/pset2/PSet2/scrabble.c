#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if(score1 > score2)
    {
        printf("player 1 wins!");
    }
    else if(score2 > score1)
    {
        printf("player 2 wins!");
    }
    else
    {
        printf("It's a tie!");
    }
}

int compute_score(string word)
{
    int score = 0;
    int wordlen = strlen(word);
    for(int i=0; i < wordlen; i++)
    {
        if(isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
            // ASCII value of A is 65, b is 66
            // in POINTS a is 0 so ASCII of char in word - 65 gives representive value in array
        }
        else if(islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }
    printf("score:%i\n", score);
    return score;
}
