#pragma once

#include <stdbool.h>

typedef struct node 
{ 
    char* data;
    struct node* next; 
} node;

void push_queue(char*);
char* pop_queue();
bool is_empty();