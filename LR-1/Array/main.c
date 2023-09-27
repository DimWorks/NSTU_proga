#include "array.h"
#include <stdio.h>

int main()
{
	ARR* array = create_array(5);
	
	array_push(&array, 1, "1");
	array_push(&array, 2, "2");
	array_push(&array, 9, "9");
	array_push(&array, 10, "10");
	array_push(NULL, 10, "10");

	print_array_string(array);

	array_pop(&array, 10, "10");
	array_pop(NULL, 10, "10");

	print_array_string(array);

	return 0;
}
