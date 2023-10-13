#pragma once

#include <stdbool.h>

//-------------------- STRUCTURE --------------------
typedef struct node 
{ 
    char* data;  
    struct node* next; 
} node;

	void push_stack(void*);
	char* pop_stack();
	bool stackIsEptpy();
