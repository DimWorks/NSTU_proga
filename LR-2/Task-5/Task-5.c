#define _CRT_SECURE_NO_WARNINGS

#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define M 4

int init_position(int x, int y)
{
	x *= 10;

	return x + y;
}

void FUCK(int x, int y)
{
	
}

bool OnBoard(int k, int s)
{
	if (k >= 1 && k <= M && s >= 1 && s <= M)
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

	push_queue(init_position(x, y));
	
	printf("\t%d\n", init_position(x, y));

	bool visited[M + 1][M + 1] = { false };
	visited[x][y] = true;

	int kMove[M + 1][M + 1] = { 0 };
	

	//printf("position: \n");

	while (!is_empty())
	{
		int z = pop_queue();
		int x_z = z / 10;
		int y_z = z % 10;

		if (x_z == X && y_z == Y)
		{
			printf("Minimum number of moves:  %d\n", kMove[x_z][y_z]);
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

				push_queue(init_position(x_new, y_new));

				printf("\t%d\n", init_position(x_new, y_new));
			}
		}
	}

	printf("ERROR: it's impossible\n");
}

int main()
{
	int x = 1, y = 4;
	letEatBee(x, y, 3, 1);
}

