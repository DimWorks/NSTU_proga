#include "queue.h"
#include <stdio.h>

int main(int argc/*Количество аргументов*/, char* argv[]/*Массив аргументов*/)
{
	for(int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}

	enqueue();

	printf("\n\tTHE END\n");

	return 0;
}
