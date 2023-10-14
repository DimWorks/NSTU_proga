#pragma once

#include <stdbool.h>

typedef struct node {
    char* key;
    void* value;
} node;

typedef struct HT {
    struct HT** items;
    struct List** overflow;
    int size;
    int count;
}HT;

typedef struct List {
    node* node;
    struct List* next;
    
} List;

HT* create_table(int size);
void ht_insert(HT* table, char* key, char* value);
char* ht_search(HT* table, char* key);
void print_search(HT* table, char* key);
void print_table(HT* table);
void ht_delete(HT* table, char* key);
void free_table(HT* table);
bool isKey(HT*table, char* key);