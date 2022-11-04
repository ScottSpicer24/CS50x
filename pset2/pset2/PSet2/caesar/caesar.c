#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    key %= 26;
    printf("key=%i\n", key);
    string word = get_string("Word in plaintext: ");
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        if(word[i] >= 65 && word[i] <= 90)
        {
            word[i] += key;
            if(word[i] > 90 )
            {
                word[i] -= 26;
            }
        }
        else if(word[i] >= 97 && word[i] <= 122)
        {
            int t = word[i] + key;
            if(t > 127)
            {
                word[i] -= 26;
            }
            word[i] += key;
            if(word[i] > 122 )
            {
                word[i] -= 26;
            }
        }
        else
        {
            word[i] += 0;
        }
    }
    printf("Word in cyiphertext: %s\n", word);
    return 0;
    check50 cs50/problems/2022/spring/caesar
}