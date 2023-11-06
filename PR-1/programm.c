#include "queue.h"
#include "stack.h"
#include "set.h"
#include "hash_table.h"
#include <stdio.h>
#include <string.h>

#define _SIZE_ 15

int main(int argc, char* argv[])
{
	//printf("What is IT? %d\n", argc);

	char* command = strdup(argv[0]);
	char* data = strdup(argv[1]);
	char* key = strdup(argv[2]);

	//printf("\nYour command: %s\n", command);
	HT* table = create_table(_SIZE_);
	SET* my_set = create_set(_SIZE_);

	//do {

		//printf("Enter it: ");
		//scanf("%s", &command);

		if (strcmp(command, "SADD") == 0)
		{
			//printf("Enter the data: ");
			//char data[100];
			//scanf("%s", data);

			printf("\nYour data: %s\n", data);

			set_insert(my_set, data, "");
		}
		else if (strcmp(command, "SPUSH") == 0)
		{
			//printf("Enter the data: ");
			//char data[100];
			//scanf("%s", data);

			printf("\nYour data: %s\n", data);

			push_stack(data);

		}
		else if (strcmp(command, "QPUSH") == 0)
		{
			//printf("Enter the data: ");
			//char data[100];
			//scanf("%s", data);

			printf("\nYour data: %s\n", data);

			push_queue(data);

		}
		else if (strcmp(command, "HSET") == 0)
		{
			//printf("Enter the data: ");
			//char data[100];
			//scanf("%s", data);

			//printf("Enter the key: ");
			//char key[100];
			//scanf("%s", key);

			printf("\nYour key: %s data: %s\n", key, data);

			ht_insert(table, key, data);
		}
		//------------REMOVE------------

		else if (strcmp(command, "SREM") == 0)
		{
			//printf("Enter the data: ");
			//char data[100];
			//scanf("%s", data);

			printf("\nYour key: %s\n", data);

			set_delete(table, data);
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
			//printf("Enter the key: ");
			//char key[100];
			//scanf("%s", key);

			printf("\nYour key: %s\n", key);

			ht_delete(table, key);
		}

		//------------READ------------
		else if (strcmp(command, "SISMEMBER") == 0)
		{
			printf("Why?\n");
		}
		else if (strcmp(command, "HGET") == 0)
		{
			//printf("Enter the key: ");
			//char key[100];
			//scanf("%s", key);

			printf("\nYour key: %s\n", key);

			print_search(table, key);
		}
		else
		{
			printf("ERROR: incorrect command\n");
		}

	//} while (1);

}
