#include "stack.h"
#include "../Lists/singly_list.h"
#include "../test.h"
#include <stdio.h>

int main()
{
	printf("\n\tTESTING STACK\n");
	char* data = "Testing";

	push_stack(data);
	push_stack("Test 2");
	push_stack("Test 3");
	push_stack("Test 4");

	pop_stack();
	pop_stack();
	pop_stack();
	pop_stack();

	return 0;
}
