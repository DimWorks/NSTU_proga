#pragma once

#include <stdbool.h>

typedef struct node 
{ 
    int data;
    struct node* next; 
} node;

void push_queue(char*);
int pop_queue();
bool is_empty();