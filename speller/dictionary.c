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

//number of buckets in hash table
const unsigned int N = 40000;

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
    //djb2 hash function for strings
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))        // *word++ is going to the next address in memory, where the next char in the string is stored
    {
        hash = ((hash << 5) + hash) + tolower(c); // hash * 33 + c   // hash << 5 = hash * 2^5
    }
    return hash % N;
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
        temp = table[i];
        while(table[i] != NULL)
        {
            temp = table[i]->next;
            free(table[i]);
            table[i] = temp;
        }
    }
    return true;
}
