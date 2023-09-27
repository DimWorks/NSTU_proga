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

void array_push(ARR** arr, int position, void* data)
{
	if (arr == NULL)
	{
		printf("ERROR: the array is empty\n");
		return;
	}

	if (position < 0)
	{
		printf("ERROR: the position can`t be less than zero\n");
		return;
	}

	ARR* array = *arr;

	if (position > array->size)
	{
		ARR* new_array = create_array(position + 1);
		node* item = (node*)malloc(sizeof(node));
		for (int i = 0; i < array->size; i++)
		{
			new_array->item[i] = array->item[i];
		}
		item->data = data;
		new_array->item[position] = item;
		new_array->size = position + 1;
		*arr = new_array;
		return;
	}
	node* item = (node*)malloc(sizeof(node));
	item->data = data;
	array->item[position] = item;
	*arr = array;
	return;
}

void array_pop(ARR** arr, int index)
{
	if (arr == NULL)
	{
		printf("ERROR: the array is empty\n");
		return;
	}

	ARR* array = *arr;

	if (index < 0 || index > array->size)
	{
		printf("ERROR: index isn`t right\n");
		return;
	}

	ARR* new_array = create_array(index);
	node* item = (node*)malloc(sizeof(node));

	for (int i = 0; i < index; i++)
	{
		new_array->item[i] = array->item[i];
	}

	for (int i = index; i < array->size; i++)
	{
		new_array->item[i] = array->item[i];
	}

	*arr = new_array;

}

void print_element(ARR* array, int index)
{
	if (array == NULL)
	{
		printf("ERROR: the array is empty\n");
		return;
	}

	if (index < 0 || index > array->size)
	{
		printf("ERROR: index isn`t right\n");
		return;
	}

	node* item = (node*)malloc(sizeof(node));

	item = array->item[index];

	if (item == NULL)
	{
		printf("%d   -   NULL\n", index);
	}
	else if (item->data == NULL)
	{
		printf("%d   -   NULL\n", index);
	}
	else
	{
		printf("%d   -   %s\n", index, item->data);
	}
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
			printf("%d   -   NULL\n", i);
		}
		else if (item->data == NULL)
		{
			printf("%d   -   NULL\n", i);
		}
		else
		{
			printf("%d   -   %s\n", i, item->data);
		}		
	}
}