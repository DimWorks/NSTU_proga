#pragma once

typedef struct node {
	void* data;
}node;

typedef struct ARR 
{
	struct ARR** item;
	node* node;
	int size;
}ARR;

ARR** create_array(int);
void array_push(ARR**, int, void*);
void print_array_string(ARR*);
void print_element(ARR*, int);
void array_pop(ARR**, int);