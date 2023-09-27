#include "array.h"
#include <stdio.h>

int main()
{
	ARR* array = create_array(5);
	
	array_push(array, 1, "1");

	print_array_string(array);

	return 0;
}
