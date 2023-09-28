#include "array.h"
#include <stdio.h>

int main()
{
	ARR* array = create_array(5);

	printf("Creating an array of size 5\n");
	
	array_push(&array, 1, "1");
	array_push(&array, 2, "2");	
	print_array_string(array);

	printf("Let's write the element by index 10\n");
	array_push(&array, 10, "10");
	print_array_string(array);
	printf("Let's write the element by index 9\n");
	array_push(&array, 9, "9");	
	print_array_string(array);
	
	printf("Delete the element by index 10\n");
	array_pop(&array, 10);
	print_array_string(array);

	return 0;
}
