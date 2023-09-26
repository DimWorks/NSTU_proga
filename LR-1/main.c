#include "test.h"
#include <stdio.h>
#include <locale.h>

int main()
{
	printf("\ttesting_hash_table\n");
	testing_hash_table();
	printf("\ttesting_list\n");
	testint_list();
	printf("\ttesting_queue\n");
	testing_queue();
	printf("\ttesting_stack\n");
	testing_stack();
	printf("\ttesting_tree\n");
	testing_tree();
	printf("It works!\n");
	return 0;
}
