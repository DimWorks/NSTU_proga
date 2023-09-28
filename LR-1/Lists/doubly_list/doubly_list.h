#pragma once

typedef struct node
{
	void* data;
	struct node* previous;
	struct node* next;
} node;

void push_to_head(node**, void*); 
void push_to_tail(node*, int); 
void push_to_position(node**, int, int);    

int pop_from_head(node**); 
int pop_from_tail(node*); 
int pop_from_position(node** , int);   

int edit_from_head(node*, int);
int edit_from_tail(node*, int);
int edit_from_position(node*, int, int);   

void print_from_head(node*); 
void print_from_tail(node*);
void print_element(node*, int);