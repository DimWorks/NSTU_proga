#include "file.h"
#include "adder.h"
#include <stdio.h>
#include <string.h>

int main(int argc/*Количество аргументов*/, char* argv[]/*Массив аргументов*/)
{
	/*printf("Enter the data: ");
	char data[100];
	scanf("%s", data);

	printf("\nYour data: %s\n", data);

	write_to_file("data.txt", "Queue", data);*/



	if (argc > 1)
	{
		if (strcmp(argv[1], "--file") == 0)
		{
			printf("path: %s\n", argv[2]);
		}

		if (strcmp(argv[3], "--query") == 0)
		{
			printf("command: %s\n", argv[4]);

			//------------ADD------------

			if (strcmp(argv[4], "SADD") == 0)
			{
				printf("Enter the data: ");
				char data[100];
				scanf("%s", data);

				printf("\nYour data: %s\n", data);

				add_set(argv[2], data, "Set");
			}
			else if (strcmp(argv[4], "SPUSH") == 0)
			{
				printf("Enter the data: ");
				char data[100];
				scanf("%s", data);

				printf("\nYour data: %s\n", data);

				
			}
			else if (strcmp(argv[4], "QPUSH") == 0)
			{
				printf("Enter the data: ");
				char data[100];
				scanf("%s", data);

				printf("\nYour data: %s\n", data);

				//write_to_file(argv[2], "Queue", data);

				add_queue(argv[2], data, "Queue");

			}
			else if (strcmp(argv[4], "HSET") == 0)
			{
				printf("Enter the data: ");
				char data[100];
				scanf("%s", data);

				printf("\nYour data: %s\n", data);
			}
			//------------REMOVE------------

			else if (strcmp(argv[4], "SREM") == 0)
			{

			}
			else if (strcmp(argv[4], "SPOP") == 0)
			{
				read_file(argv[2], "Stack");
			}
			else if (strcmp(argv[4], "QPOP") == 0)
			{
				read_file(argv[2], "Queue");
			}
			else if (strcmp(argv[4], "HDEL") == 0)
			{

			}

			//------------READ------------
			else if (strcmp(argv[4], "SISMEMBER") == 0)
			{
				read_file(argv[2], "Set");
			}
			else if (strcmp(argv[4], "HGET") == 0)
			{
				read_file(argv[2], "HT");
			}
			else
			{
				printf("ERROR: incorrect command\n");
			}

		}
	}
	else
	{
		printf("ERROR: incorrect arguments\nUse the entry form: ./program.out --file <path to file> --query <command>\n");
	}

	return 0;
}