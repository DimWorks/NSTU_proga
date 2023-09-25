#include "queue.h"
#include "../Lists/singly_list.h"

void push_queue(void* data)
{
	push_to_tail(TAIL, data);
}

void pop_queue()
{
	printf("%s\n", pop_from_head(&HEAD));
}