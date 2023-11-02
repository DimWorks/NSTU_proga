#pragma once

//-------------------- STRUCTURE --------------------
typedef struct s_node
{
	char* data;
	struct s_node* next;
} s_node;

	void push_stack(char*);
	char* pop_stack();
