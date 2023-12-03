#pragma once


class Array
{
	int size;
	int* arr;
public:
	Array(int s) { size = s; arr = new int[size]; for (int i = 0; i < size; i++) { arr[i] = 10101; } }
	void set(int index, int data);
	int get(int index);
};

