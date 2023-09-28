#include "queue.h"
#include "../test.h"
#include <stdio.h>

int main()
{
	printf("\n\tTESTING QUEUE\n");
	char* data = "Test 1";
	printf("push to queue: %s\n", data);
	push_queue(data);
	data = "Test 2";
	printf("push to queue: %s\n", data);
	push_queue(data);
	data = "Test 3";
	printf("push to queue: %s\n", data);
	push_queue(data);
	data = "Test 4";
	printf("push to queue: %s\n", data);
	push_queue(data);

	printf("Read from queue: ");
	pop_queue();
	printf("Read from queue: ");
	pop_queue();
	printf("Read from queue: ");
	pop_queue();
	printf("Read from queue: ");
	pop_queue();
	printf("Read from queue: ");
	pop_queue();

	return 0;
}