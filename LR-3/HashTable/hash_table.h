#pragma once
class node
{
	friend class hash_table;
public:
	int key;
	int data;
	node* next;
};

class hash_table
{
	static const int TABLE_SIZE = 100;
	node* table[TABLE_SIZE];
public:
	hash_table() { for (int i = 0; i < TABLE_SIZE; i++) { table[i] = nullptr; } };
	void insert(int key, int data);
	int get(int key);
	void remove(int key);
};

