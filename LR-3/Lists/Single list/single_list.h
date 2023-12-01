#pragma once

class node
{
	friend class single_list;
public:
	int data;
	node* next;
};

class single_list
{
private:
	node* head;
	node* tail;
	int size;

public:
	single_list() { head = nullptr; tail = head; size = 0; }
	void push_to_head(int data);
	void push_to_tail(int data);
	void print_from_head();
	int pop_from_head();
	int pop_from_tail();
	int pop_from_position(int position);
};
