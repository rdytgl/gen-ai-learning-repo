// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 65536; // 2^16 is the largest bucket that will allow for least collisions but
                              // also not too large to waste memory

unsigned int word_count = 0;
bool dictionary_loaded = false;

// Hash table
node *table[N];
int bucket_sizes[N] = {0};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char temp[LENGTH + 1];
    int i = 0;

    // turns the word to lower-case to account for case-insensitivity
    while (word[i] && i < LENGTH)
    {
        temp[i] = tolower(word[i]);
        i++;
    }
    temp[i] = '\0';

    // hashes the lower-cased word to get the index of the bucket
    int index = hash(temp);

    // traverses the linked list in the bucket
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcmp(cursor->word, temp) == 0)
        {
            return true;
        }
        // checks the next word if first word is not checked
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 19; // initial hash value
    int i = 0;

    while (word[i] != '\0')
    {
        char c = tolower(word[i]);
        hash = hash * 31 +
               c * (i + 1); // this hash function takes the initial hash value and multiplies it
                            // with another prime; then adds the product of the letter's ascii value
                            // and its position to avoid collisions with similar word patterns
        i++;
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the dictionary
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false;
    }

    char word[LENGTH + 1]; // buffer to hold a word

    // read the words
    while (fscanf(source, "%s", word) != EOF)
    {
        // malloc
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            return false;
        }

        // copy word to the new node
        strcpy(new_node->word, word);

        // hash the word to be inserted to the bucket
        unsigned int index = hash(word);
        bucket_sizes[index]++;

        // insert the linked list into the hash table (prepend menthod)
        new_node->next = table[index];
        table[index] = new_node;

        word_count++;
    }

    // close dictionary
    fclose(source);

    // to be deleted later
    // hash checker
    // int total = 0;
    // int non_empty = 0;
    // int max = 0;
    // int samples_shown = 0;

    // printf("\n--- Hash Table Stats ---\n");

    // for (int i = 0; i < N; i++)
    // {
    // int size = bucket_sizes[i];
    // total += size;
    // if (size > 0)
    // {
    // non_empty++;
    // if (size > max)
    // {
    // max = size;
    // }

    // Show sample of first few buckets (e.g., 10)
    // if (samples_shown < 10)
    // {
    // printf("Bucket %d: %d words\n", i, size);
    // samples_shown++;
    // }
    // }
    // }

    // printf("Total words loaded: %d\n", total);
    // printf("Non-empty buckets: %d (%.2f%%)\n", non_empty, 100.0 * non_empty / N);
    // printf("Average words per non-empty bucket: %.2f\n", (float) total / non_empty);
    // printf("Max bucket size: %d\n\n", max);

    // visualise bucket distribution
    // printf("\n--- Bucket Histogram ---\n");

    // int bins[10] = {0}; // Group buckets by size ranges: 0-9, 10-19, ..., 90+
    // for (int i = 0; i < N; i++)
    // {
    // int size = bucket_sizes[i];
    // if (size == 0)
    // continue;

    // if (size >= 90)
    // bins[9]++;
    // else
    // bins[size / 10]++;
    // }

    // for (int i = 0; i < 10; i++)
    // {
    // int lower = i * 10;
    // int upper = (i == 9) ? 90 : (lower + 9);

    // printf("%2d–%2d words: %5d buckets | ", lower, upper, bins[i]);

    // int bar_length = bins[i] / 100; // Adjust scale if needed
    // for (int j = 0; j < bar_length; j++)
    // {
    // printf("#");
    // }
    // printf("\n");
    // }

    // keep this code
    dictionary_loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // if dictionary exists
    if (dictionary_loaded)
    {
        // return word_count
        return word_count;
    }
    // else
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
