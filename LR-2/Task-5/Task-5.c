#define _CRT_SECURE_NO_WARNINGS

#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 4

char* init_position(int x, int y)
{
	char position[4];
	position[0] = x + '0';// 48;
	position[1] = ' ';
	position[2] = y + 48;
	position[3] = '\0';

	

	return position;
}

void FUCK(int x, int y)
{
	
}

void get_position(char* position)
{
	printf("%d ", position[0]-48);
	printf("%d\n", position[2]-48);
	////printf("\n");
}

bool OnBoard(int k, int s)
{
	if (k > 2 && k < M + 1 && s > 0 && s < M + 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void letEatBee(int x, int y, int X, int Y)
{
	int dx[8] = { -2, -1, 1, 2, -2, -1, 1, 2 };
	int dy[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };	
	char tmp[4];

	strncpy(tmp, init_position(x, y), 4);
	push_queue(tmp);
	printf("\t%s\n", tmp);

	bool visited[M + 1][M + 1] = { false };
	visited[x][y] = true;

	int kMove[M + 1][M + 1] = { 0 };
	

	//printf("position: \n");

	while (!is_empty())
	{
		char* z = pop_queue();
		int x_z = z[0] - 48;
		int y_z = z[2] - 48;

		if (x_z == X && y_z == Y)
		{
			printf("YES!\t%d\n", kMove[x_z][y_z]);
			return;
		}

		for (int i = 0; i < 8; i++)
		{
			int x_new = x_z + dx[i];
			int y_new = y_z + dy[i];

			if (OnBoard(x_new, y_new) && !visited[x_new][y_new])
			{
				visited[x_new][y_new] = true;
				kMove[x_new][y_new] = kMove[x_z][y_z] + 1;

				strncpy(tmp, init_position(x_new, y_new), 4);
				push_queue(tmp);
				printf("\t%s\n", tmp);
			}
		}
	}

	printf("ERROR: it's impossible\n");
}

int main()
{
	int x = 1, y = 4;
	letEatBee(x, y, 1, 3);
}

