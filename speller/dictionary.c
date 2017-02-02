/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include "dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<ctype.h>
#include <math.h>

/**
 * Returns true if word is in dictionary else false.
 */
    #define SIZE 1000000
    int dictionarySize = 0;
    
    typedef struct node
    {
        char word [LENGTH + 1];
        struct node* next;
    }
    node;
    
    node *hashtable[SIZE] = {NULL};
    
int hash (const char* word)
{
    int hash = 0;
    int n;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // alphabet case
        if(isalpha(word[i]))
            n = word [i] - 'a' + 1;
        
        // comma case
        else
            n = 27;
            
        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;    
}
 
 
bool check(const char *word)
{
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
        temp[len] = '\0';
    }
    
    
    
    int index = hash(temp);
    node *cursor = hashtable[index];
    
    if(hashtable[index] == NULL)
    {
        return false;
    }
    while(cursor != NULL)
    {
        if(strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE* file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while(fscanf(file, "%s", word)!= EOF)
    {
        node *new_node = malloc(sizeof(node));
        strcpy(new_node->word, word);
        dictionarySize++;
        int index = hash(word);
        if (hashtable[index] == NULL)
        {
            hashtable[index] = new_node;
            new_node->next = NULL;
        }
        
        
        else
        {
            new_node->next = hashtable[index];
            hashtable[index] = new_node;
            
        }
       
    }
    fclose(file);
    return true;
    
   
    // TODO

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if(dictionarySize > 0)
    {
        return dictionarySize;
    }
    else
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
      
    int index = 0;
   
    
    while(index < SIZE)
    {
        if(hashtable[index] == NULL)
        {
            index++;
        }
    
        else
         {
             while(hashtable[index] != NULL)
                {
                     node *cursor = hashtable[index];
                     hashtable[index] = cursor->next;
                     free(cursor);
     
                }
            index++;
    
        }
    }
    return true;
}

