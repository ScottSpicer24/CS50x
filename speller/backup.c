// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];
node *n = NULL;
node *temp;
unsigned int dsize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int i = hash(word);
    temp = table[i];
    while(temp != NULL)
    {
        if(strcasecmp(temp->word, word) == 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Hashes word from dictionary to a number
unsigned int hash(const char *word)
{
    int k = toupper(word[0] - 'A');
    k *= 26;
    int j = toupper(word[1] - 'A');
    int i = k + j;
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fp = fopen(dictionary, "r");
    if(fp==NULL)
    {
        return false;
    }
    char tempword[LENGTH + 1];
    while(fscanf(fp, "%s", tempword) != EOF)
    {
        unsigned int i = hash(tempword);
        n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }
        else
        {
            strcpy(n->word, tempword);
            if(table[i] == NULL)
            {
                table[i] = n;
            }
            else
            {
                n->next = table[i];
                table[i] = n;
            }
            dsize++;
        }
    }

        /* OLD ONE
        if(table[i] == NULL)
        {
            table[i] = malloc(sizeof(node));
            if(table[i] == NULL)
            {
                fclose(fp);
                return false;
            }
            strcpy(table[i]->word, tempword);
        }
        else
        {
            table[i] = n;
            while(n->next != NULL)
            {
                n = n->next;
            }
            temp = n;
            n = malloc(sizeof(node));
            if(n==NULL)
            {
                fclose(fp);
                return false;
            }
            else
            {
                temp->next = n;
                n->next = NULL;
                strcpy(n->word, tempword);
            }
        }
    }
    */
    //size(); think this is not needed
    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size()
{
    return dsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i > N; i++)
    {
        while(table[i] != NULL)
        {
            table[i] = temp;
            temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
