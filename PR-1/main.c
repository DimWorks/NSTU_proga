#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define _SIZE_ 25

void call_dataBase(char* command, char* data, char* key)
{
	pid_t pid = -2;

	switch(pid = fork())
	{
	case -1:
		printf("ERROR: fork()");

		break;
	case 0:
		char* path = "/home/dima/NSTU_proga/PR-1/dataBase.out\0";
		execl(path, command, data, key, NULL);
		//return;

		break;
	default:
		break;
	}
}

int main()
{
	char command[_SIZE_];
	printf("Enter the command: ");
	scanf("%s", command);

	printf("Enter the data: ");
	char data[_SIZE_];
	scanf("%s", data);

	printf("Enter the key: ");
	char key[_SIZE_];
	scanf("%s", key);

	call_dataBase(command, data, key);
	
}
