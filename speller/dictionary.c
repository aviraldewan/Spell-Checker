// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdint.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 143091;
int hash_value = 0;
unsigned int word_count = 0;
unsigned int hav = 0;

int a = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
//Source: https://discord.com/channels/393846237255696385/395685061678071808/671574940641656842
unsigned int hash(const char *word)
{
    // TODO
    uint32_t hash = 0;

    char *tmp = malloc(strlen(word) + 1);
    if (tmp == NULL)
    {
        return 1;
    }
    char *f = tmp;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isupper(word[i]))
        {
            tmp[i] = tolower(word[i]);
        }
        else
        {
            tmp[i] = word[i];
        }
        tmp[n] = '\0';
    }

    while (*tmp)
    {
        hash = (hash << 2) ^ *tmp;
        tmp++;
    }

    free(f);

    // return a value between 0 and 65535
    return (int)((hash >> 16) ^ (hash & 0xffff));
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        fclose(input);
        return false;
    }

    char w[LENGTH + 1];
    int hv = 0;

    while (fscanf(input, "%s", w) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(input);
            return 1;
        }
        if (strcmp(" ", w) != 0)
        {
            strcpy(n->word, w);
            word_count++;
        }

        n->next = NULL;

        hash_value = hash(n->word);

        if (table[hash_value] == NULL)
        {
            table[hash_value] = n;
        }
        else
        {
            n->next = table[hash_value];
            table[hash_value] = n;
        }
        if (word_count == 0)
        {
            a = hash_value;
        }
    }


    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (word_count > 0)
    {
        return word_count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *now = table[i];
        while (now != NULL)
        {
            node *tmp = now->next;
            free(now);
            now = tmp;
        }
    }

    return true;
}