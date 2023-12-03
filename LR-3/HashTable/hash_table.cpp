#include "hash_table.h"



void hash_table::insert(int key, int data) {
    int index = key % TABLE_SIZE;

    node* newnode = new node;
    newnode->key = key;
    newnode->data = data;
    newnode->next = nullptr;

    if (table[index] == nullptr) 
    {
        table[index] = newnode;
    }
    else 
    {
        node* current = table[index];

        while (current->next != nullptr) 
        {
            current = current->next;
        }
        current->next = newnode;
    }
}

int hash_table::get(int key) 
{
    int index = key % TABLE_SIZE;

    node* current = table[index];

    while (current != nullptr) 
    {
        if (current->key == key) 
        {
            return current->data;
        }
        current = current->next;
    }

    return -1; // Key not found
}

void hash_table::remove(int key) 
{
    int index = key % TABLE_SIZE;

    node* current = table[index];
    node* prev = nullptr;
    while (current != nullptr) 
    {
        if (current->key == key) 
        {
            if (prev == nullptr) 
            {
                table[index] = current->next;
            }
            else 
            {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}