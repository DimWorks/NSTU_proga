#include "set.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define CAPACITY 10 // Size of the Hash Table



//-----------------HASH FUNCK-------------------------------

unsigned long hash(char* str)
{
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
    {
        i += str[j];
    }
    return i % CAPACITY;
}

//-----------------CREATE HASH TABLE--------------------

node* create_node(char* key, char* value)
{
    node* item = (node*)malloc(sizeof(node));
    item->key = (char*)malloc(strlen(key) + 1);

    if (key != 0)
    {
        strcpy(item->key, key);
    }

    return item;
}

SET* create_set(int size)
{
    SET* table = (SET*)malloc(sizeof(SET));
    table->size = size;
    table->count = 0;
    table->items = (node**)calloc(table->size, sizeof(node*));
    for (int i = 0; i < table->size; i++)
    {
        table->items[i] = NULL;
    }

    return table;
}

void free_node(node* item)
{
    // Frees an item
    free(item->key);
    free(item);
}

void free_set(SET* table)
{
    // Frees the table
    for (int i = 0; i < table->size; i++)
    {
        node* item = table->items[i];
        if (item != NULL)
        {
            free_node(item);
        }
    }

    free(table->items);
    free(table);
}

//----------------------PUSH TO HASH TABLE-------------------

void set_insert(SET* table, char* key, char* value)
{
    if (table == NULL)
    {
        return;
    }
    // Create the item
    node* item = create_node(key, value);

    int index = hash_function(key);

    node* current_item = table->items[index];

    if (current_item == NULL)
    {
        // Key does not exist.
        if (table->count == table->size)
        {
            printf("Insert Error: Hash Table is full\n");
            return;
        }

        // Insert directly
        table->items[index] = item;
        table->count++;
    }
    else
    {
        printf("Insert Error: The element already exists\n");
        return;
    }
}

char* set_search(SET* table, char* key)
{
    int index = hash(key);


    for (int i = 0; i < table->size; i++)
    {
        node* item = table->items[index];
        if (item == NULL)
        {
            return NULL;
        }
        else if (strcmp(item->key, key) == 0)
        {
            return item->key;
        }
    }
    return NULL;
}

void search_print(SET* table, char* key)
{
    char* val;
    if ((val = set_search(table, key)) == NULL)
    {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_set(SET* table)
{
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            node* tmp = table->items[i];
            printf("Index:%d, Key:%s\n", i, tmp->key);
        }
    }
    printf("-------------------\n\n");
}

void set_delete(SET* table, char* key)
{
    // Deletes an item from the table
    int index = hash(key);
    //node* item = table->items[index];

    if (table->items[index] == NULL)
    {
        return;
    }

    table->items[index] = NULL;
}