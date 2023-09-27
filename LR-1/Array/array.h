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
void array_push(ARR*, int, int);
void print_array_string(ARR*);