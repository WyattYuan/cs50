// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10007;

// Hash table
node *table[N];

// count the words loaded
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node* trav = table[hash(word)];
    while(trav != NULL)
    {
        if(strcasecmp(trav -> word,word) == 0)
        {
            return true;
        }
        trav = trav -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash += (hash << 2) ^ tolower(word[i]);
        // case insensitive hash function
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open the dictionary file
    FILE* dict = fopen(dictionary,"r");
    if(dict == NULL)
    {
        return false;
    }
    // read the file line by line
    char buffer[LENGTH + 1];
    unsigned int index = 0;
    while (fscanf(dict, "%45s", buffer) != EOF)
    {
        node* new = malloc(sizeof(node));
        if (new == NULL)
        {
            fclose(dict);
            return false;
        }

        strcpy(new->word, buffer);

        new->next = NULL;

        index = hash(new->word);
        new -> next = table[index];
        table[index] = new;
        count++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}


// Unloads dictionary from memory, returning true if successful, else false
void clear(node* tobedel)
{
    if (tobedel == NULL)
    {
        return;
    }
    clear(tobedel->next);
    free(tobedel);
}
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        if (table[i] != NULL) {
            clear(table[i]);
        }
    }
    return true;
}
