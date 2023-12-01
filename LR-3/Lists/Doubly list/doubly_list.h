#pragma once

class node
{
	friend class doubly_list;
public:
	int data;
	node* next;
	node* prev;
};

class doubly_list
{
private:
	node* head;
	node* tail;
	int size;

public:
	doubly_list() { head = nullptr; tail = head; size = 0; }
	void push_to_head(int);
	void push_to_tail(int);

	int pop_from_head();
	int pop_from_tail();
	int pop_from_position(int);

	void print_from_head();
	void print_from_tail();
};

