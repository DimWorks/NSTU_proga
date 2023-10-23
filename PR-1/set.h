#pragma once

typedef struct node {
    char* key;
} node;

typedef struct SET {
    struct SET** items;
    int size;
    int count;
}SET;

void set_insert(SET*, char*);
void search_print(SET*, char*);
void print_set(SET*);
void set_delete(SET*, char*);
void free_set(SET*);