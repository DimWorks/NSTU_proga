#include "queue.h"
#include "stack.h"
#include "set.h"
#include "hash_table.h"
#include <stdio.h>

#define _SIZE_ 15

int main()
{
	char command[_SIZE_];

	do {

		printf("Enter it: ");
		scanf("%s", &command);

		if (strcmp(command, "SADD") == 0)
		{
			printf("Enter the data: ");
			char data[100];
			scanf("%s", data);

			printf("\nYour data: %s\n", data);


		}
		else if (strcmp(command, "SPUSH") == 0)
		{
			printf("Enter the data: ");
			char data[100];
			scanf("%s", data);

			printf("\nYour data: %s\n", data);

			push_stack(data);

		}
		else if (strcmp(command, "QPUSH") == 0)
		{
			printf("Enter the data: ");
			char data[100];
			scanf("%s", data);

			printf("\nYour data: %s\n", data);

			push_queue(data);

		}
		else if (strcmp(command, "HSET") == 0)
		{
			printf("Enter the data: ");
			char data[100];
			scanf("%s", data);

			printf("\nYour data: %s\n", data);
		}
		//------------REMOVE------------

		else if (strcmp(command, "SREM") == 0)
		{

		}
		else if (strcmp(command, "SPOP") == 0)
		{
			printf("%s\n", pop_stack());
		}
		else if (strcmp(command, "QPOP") == 0)
		{
			printf("%s\n", pop_queue());
		}
		else if (strcmp(command, "HDEL") == 0)
		{

		}

		//------------READ------------
		else if (strcmp(command, "SISMEMBER") == 0)
		{

		}
		else if (strcmp(command, "HGET") == 0)
		{

		}
		else
		{
			printf("ERROR: incorrect command\n");
		}

	} while (1);

}