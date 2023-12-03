#include "array.h"
#include <iostream>

using namespace std;

void Array::set(int index, int data)
{
	if (index < 0 )
	{
		cout << "ERROR: The position can`t be less than zero\n";
	}
	else if (index >= size)
	{
		size = index + 1;
		int* newArr = new int[size];

		for (int i = 0; i < index; i++)
		{
			newArr[i] = arr[i];
		}
		delete[] arr;
		arr = newArr;
	}
	arr[index] = data;
}

int Array::get(int index)
{
	if (index < 0 || index >= size)
	{
		cout << "ERROR: Index out of range\n";
	}

	return arr[index];
}