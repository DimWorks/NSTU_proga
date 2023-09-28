#include "stack.h"
#include "../test.h"
#include <stdio.h>

int main()
{
	printf("\n\tTESTING STACK\n");
	char* data = "Test 1";
	printf("push to stack: %s\n", data);
	push_stack(data);
	data = "Test 2";
	printf("push to stack: %s\n", data);
	push_stack(data);
	data = "Test 3";
	printf("push to stack: %s\n", data);
	push_stack(data);
	data = "Test 4";
	printf("push to stack: %s\n", data);
	push_stack(data);

	printf("Read from stack: ");
	pop_stack();
	printf("Read from stack: ");
	pop_stack();
	printf("Read from stack: ");
	pop_stack();
	printf("Read from stack: ");
	pop_stack();
	printf("Read from stack: ");
	pop_stack();

	return 0;
}
