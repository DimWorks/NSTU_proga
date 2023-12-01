#include "single_list.h"
#include <iostream>

using namespace std;

int count(node* list_copy)
{
	int x = 0;
	//обход всего списока
	for (; list_copy != NULL; list_copy = list_copy->next)
	{
		x++;
	}
	return x;
}

//-------------------- PUSH FUNCTION --------------------

void single_list::push_to_head(int data)
{
	node* newNode = new node();
	newNode->data = data;
	newNode->next = NULL;
	
	if (head != NULL)
	{
		newNode->next = head;
	}
	head = newNode;
	size++;
}

void single_list::push_to_tail(int data)
{
	if (head == NULL)
	{
		push_to_head(data);
		tail = head;
		return;
	}
	node* tmp = new node();
	tmp->data = data;
	tmp->next = NULL;

	node* list = head;

	while ((list->next) != NULL)
	{
		list = list->next;
	}
	list->next = tmp;
	tail = list;
	size++;
}

//-------------------- POP FUNCTION --------------------

int single_list::pop_from_head()
{
	if (head == NULL)
	{
		cout << "Element doesn't exist. List is empty.\n";
		return NULL;
	}
	node* tmp = head;
	int res = tmp->data;
	head = tmp->next;
	free(tmp);
	size--;
	return res;
}

int single_list::pop_from_tail()
{
	if (head == NULL)
	{
		printf("Element doesn't exist. List is empty.\n");
		return NULL;
	}
	node* tmp = head;
	node* list = head;
	while (list->next != NULL)
	{
		tmp = list;
		list = list->next;
	}
	int res = list->data;
	tmp->next = NULL;
	free(list);
	size--;
	return res;
}

int single_list::pop_from_position(int position)
{
	if (head == NULL)
	{
		printf("Element to remove doesn't exist. List is empty.\n");
		return NULL;
	}

	if (position < 1 || position > size)
	{
		printf("Impossible position for the element\n");
		return NULL;
	}
	if (position == 1)
	{
		return pop_from_head();
	}
	if (position == size)
	{
		return pop_from_tail();
	}
	node* list_copy = head;
	node* tmp = list_copy;
	for (int i = 1; i < position; i++, list_copy = (list_copy)->next)
	{
		tmp = list_copy;
	}
	int res = list_copy->data;
	tmp->next = list_copy->next;
	free(list_copy);
	size--;
	return res;
}

//-------------------- PRINT FUNCTION --------------------

void single_list::print_from_head()
{
	if (head == nullptr)
	{
		cout << "List is empty\n";
		return;
	}
	node* tmp = head;
	cout << "List is: ";
	while (tmp != nullptr)
	{
		cout << tmp->data << "; ";
		tmp = tmp->next;
	}

	cout << endl;
}

