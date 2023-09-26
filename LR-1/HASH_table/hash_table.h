#pragma once

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

void ht_insert(HT*, char* , char*);
void print_search(HT*, char*);
void print_table(HT*);
void ht_delete(HT*, char*);
void free_table(HT*);