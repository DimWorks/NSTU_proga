#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define CAPACITY 10 // Size of the Hash Table

List* HEAD;
List* TAIL;


//-----------------HASH FUNCK-------------------------------

unsigned long hash_function(char* str)
{
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
    {
        i += str[j];
    }

    return i % CAPACITY;
}

//-----------------CREATE HASH TABLE--------------------

ht_node* create_item(char* key, char* value)
{
    ht_node* item = (ht_node*)malloc(sizeof(ht_node));
    item->key = (char*)malloc(strlen(key) + 1);
    item->value = (char*)malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

List** create_overflow(HT* table)
{
    List** my_list = (List**)calloc(table->size, sizeof(List*));
    for (int i = 0; i < table->size; i++)
    {
        my_list[i] = NULL;
    }
    return my_list;
}

HT* create_table(int size)
{
    HT* table = (HT*)malloc(sizeof(HT));
    table->size = size;
    table->count = 0;
    table->items = (ht_node**)calloc(table->size, sizeof(ht_node*));
    for (int i = 0; i < table->size; i++)
    {
        table->items[i] = NULL;
    }
    table->overflow = create_overflow(table);
    return table;
}

void free_list(List* list)
{
    List* temp = list;
    while (list != NULL)
    {
        temp = list;
        list = list->next;
        free(temp->ht_node->key);
        free(temp->ht_node->value);
        free(temp->ht_node);
        free(temp);
    }
}

void free_overflow(HT* table)
{
    List** my_list = table->overflow;
    for (int i = 0; i < table->size; i++)
    {
        free_list(my_list[i]);
    }
    free(my_list);
}

void free_item(ht_node* item)
{
    // Frees an item
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HT* table)
{
    // Frees the table
    for (int i = 0; i < table->size; i++)
    {
        ht_node* item = table->items[i];
        if (item != NULL)
        {
            free_item(item);
        }
    }

    free_overflow(table);
    free(table->items);
    free(table);
}

List* list_insert(List* list, ht_node* item)
{
    if (list == NULL)
    {
        list = (List*)malloc(sizeof(List));
        list->ht_node = item;
        list->next = NULL;
        return list;
    }
    else if (list->next == NULL)
    {
        List* tmp = (List*)malloc(sizeof(List));
        tmp->ht_node = item;
        tmp->next = NULL;
        list->next = tmp;
        return list;
    }
    else
    {
        while (list->next != NULL)
        {
            list = list->next;
        }
        List* tmp = (List*)malloc(sizeof(List));
        tmp->ht_node = item;
        tmp->next = NULL;
        list->next = tmp;
        return list;
    }
}

void handle_collision(HT* table, unsigned long index, ht_node* item)
{
    List* list = table->overflow[index];

    if (list == NULL)
    {
        // We need to create the list
        list = (List*)malloc(sizeof(List));
        list->ht_node = item;
        list->next = NULL;
        table->overflow[index] = list;

        return;
    }
    else {
        // Insert to the list
        table->overflow[index] = list_insert(list, item);
        return;
    }
}

//----------------------PUSH TO HASH TABLE-------------------

void ht_insert(HT* table, char* key, char* value)
{
    if (table == NULL)
    {
        return;
    }
    // Create the item
    ht_node* item = create_item(key, value);

    int index = hash_function(key);

    ht_node* current_item = table->items[index];

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
        // Scenario 1: We only need to update value
        if (strcmp(current_item->key, key) == 0)
        {
            strcpy(current_item->value, value);
            //strcpy(table->items[index], current_item->value);
            return;
        }
        else
        {
            // Scenario 2: Collision
            // We will handle case this a bit later
            handle_collision(table, index, item);
            return;
        }
    }
}

char* ht_search(HT* table, char* key)
{
    int index = hash_function(key);
    ht_node* item = table->items[index];
    List* list = table->overflow[index];

    // Ensure that we move to a non NULL item
    while (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
        {
            return item->value;
        }

        if (list == NULL)
        {
            return NULL;
        }

        item = list->ht_node;
        list = list->next;
    }
    return NULL;
}

void print_search(HT* table, char* key)
{
    char* val;
    if ((val = ht_search(table, key)) == NULL)
    {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_table(HT* table)
{
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < table->size; i++)
    {
        if (table->items[i])
        {
            ht_node* tmp = table->items[i];
            printf("Index:%d, Key:%s, Value:%s\n", i, tmp->key, tmp->value);
        }
    }
    printf("-------------------\n\n");
}

void ht_delete(HT* table, char* key)
{
    // Deletes an item from the table
    int index = hash_function(key);
    ht_node* item = table->items[index];
    List* head = table->overflow[index];

    if (item == NULL)
    {
        // Does not exist. Return
        return;
    }
    else
    {
        if (head == NULL && strcmp(item->key, key) == 0)
        {
            // No collision chain. Remove the item
            // and set table index to NULL
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }
        else if (head != NULL)
        {
            // Collision Chain exists
            if (strcmp(item->key, key) == 0)
            {
                // Remove this item and set the head of the list
                // as the new item

                free_item(item);
                List* list = head;
                head = head->next;
                list->next = NULL;

                table->items[index] = create_item(list->ht_node->key, list->ht_node->value);
                free_list(list);
                table->overflow[index] = head;
                return;
            }

            List* curr = head;
            List* prev = NULL;

            while (curr)
            {
                if (strcmp(curr->ht_node->key, key) == 0)
                {
                    if (prev == NULL)
                    {
                        // First element of the chain. Remove the chain
                        free_list(head);
                        table->overflow[index] = NULL;
                        return;
                    }
                    else
                    {
                        // This is somewhere in the chain
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_list(curr);
                        table->overflow[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }

        }
    }
}