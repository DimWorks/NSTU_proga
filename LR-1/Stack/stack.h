#pragma once

//-------------------- STRUCTURE --------------------
typedef struct node 
{ 
    void* data;  
    struct node* next; 
} node;

	void push_stack(void*);
	void pop_stack();
