#pragma once

class node
{
	friend class queue;
public:
	int data;
	node* next;
};

class queue
{
	node* head;
	node* tail;
public:
	queue() {}
	void push_queue(int);
	int pop_queue();
};

