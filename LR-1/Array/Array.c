#include "array.h"
#include <stdio.h>
#include <stdlib.h>

ARR** create_array(int size)
{
	ARR* array = (ARR*)malloc(sizeof(ARR));
	array->item = (ARR**)calloc(size, sizeof(ARR*));
	array->size = size;
	for (int i = 0; i < size; i++)
	{
		array->item[i] = NULL;
	}
	return array;
}

void array_push(ARR* array, int position, void* data)
{
	if (position < 0)
	{
		printf("ERROR: the position can`t be less than zero\n");
		return;
	}

	if (position > array->size)
	{
		ARR* new_array = create_array(position + 1);
		node* item = (node*)malloc(sizeof(node));
		item->data = data;
		new_array->item[position] = item;
		array = new_array;
		return;
	}
	node* item = (node*)malloc(sizeof(node));
	item->data = data;
	array->item[position] = item;
}

void print_array_string(ARR* array)
{
	if (array == NULL)
	{
		printf("ERROR: the array is empty\n");
		return;
	}

	node* item = (node*)malloc(sizeof(node));

	for (int i = 0; i < array->size; i++)
	{
		item = array->item[i];

		if (item == NULL)
		{
			printf("%d   -   NULL\n");
		}
		else if (item->data == NULL)
		{
			printf("%d   -   NULL\n");
		}
		else
		{
			printf("%d   -   %s\n", item->data);
		}		
	}
}