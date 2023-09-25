#include "queue.h"
#include "../Lists/singly_list.h"
#include <stdio.h>

void testing_queue()
{

	printf("\n\tTESTING QUEUE\n");
	push_queue(data);
	push_queue("My test 2");
	push_queue("My test 3");
	push_queue("My test 4");

	pop_queue();
	pop_queue();
	pop_queue();
	pop_queue();
}