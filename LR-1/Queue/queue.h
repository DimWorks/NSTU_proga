#pragma once

typedef struct node 
{ 
    void* data;  
    struct node* next; 
} node;

void push_queue(void*);
void pop_queue();
