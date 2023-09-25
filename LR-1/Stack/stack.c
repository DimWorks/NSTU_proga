#include "stack.h"
#include "../Lists/singly_list.h"

node* HEAD;
node* TAIL;

void push_stack(void* data)
{
	push_to_head(&HEAD, data);
}

void pop_stack()
{
	printf("%s\n", pop_from_head(&HEAD));
}