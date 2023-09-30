//#include "queue.h"
#include <stdio.h>
#include <string.h>

int main(int argc/*Количество аргументов*/, char* argv[]/*Массив аргументов*/)
{
	/*for(int i = 0; i < argc; i++)
	{
		printf("%d - %s\n", i, argv[i]);
	}*/

	
	if(argc > 1)
	{
		if(strcmp(argv[1], "--file") == 0)
		{
			printf("path: %s\n", argv[2]);
		}

		if(strcmp(argv[3], "--query") == 0)
		{
			//------------ADD------------

			if(strcmp(argv[4], "SADD") == 0)
			{
				printf("Enter the data: ");
				char data[100];
				scanf("%s", data);
			
				printf("\nYour data: %s\n", data);
			}
			else if(strcmp(argv[4], "SPUSH") == 0)
			{
			
			}
			else if(strcmp(argv[4], "QPUSH") == 0)
			{
			
			}
			else if(strcmp(argv[4], "HSET") == 0)
			{
			
			}
			else
			{
				printf("ERROR: Incorect command\n");
			}
		//------------REMOVE------------
		
		//------------READ------------
	
		}
	}
	else
	{
		printf("ERROR: \n");
	}
	printf("\n\tTHE END\n");

	return 0;
}
