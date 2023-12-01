#include "doubly_list.h"
#include <iostream>

using namespace std;

int count(node* list_copy)
{
    int x = 0;

    for (; list_copy != NULL; list_copy = list_copy->next)
    {
        x++;
    }
    return x;
}


void doubly_list::push_to_head(int data)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = head;
    tmp->prev = NULL;

    if (head != NULL)
    {
        tmp->next->prev = tmp;
    }
    else
    {
        tail = tmp;
    }
    //*list = tmp;
    head = tmp;
    size++;
}

void doubly_list::push_to_tail(int data)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = NULL;
    if (tail == NULL)
    {
        tail = tmp;
    }
    else
    {
        tmp->prev = tail;
        tmp->prev->next = tmp;
        tail = tmp;
    }
    size++;
}

int doubly_list::pop_from_head()
{
    if (head == NULL)
    {
        printf("Element to remove doesn't exist. List is empty.\n");
        return NULL;
    }
    node* tmp = head;
    int res = tmp->data;
    head = tmp->next;
    free(tmp);
    size--;
    return res;
}

int doubly_list::pop_from_tail()
{
    if (head == NULL)
    {
        printf("Element to remove doesn't exist. List is empty.\n");
        return NULL;
    }

    node* tmp = tail;
    tail = tail->prev;
    tail->next = NULL;
    int res = tmp->data;
    free(tmp);
    size--;
    return res;
}


int doubly_list::pop_from_position(int position)
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

void  doubly_list::print_from_head()
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    node* list = head;
    printf("Print from HEAD: ");
    while (list != NULL)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    cout << endl;
}

void  doubly_list::print_from_tail()
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    node* list = tail;
    printf("Print from TAIL: ");
    // Тут залодена ошибка
    while (list != NULL)
    {
        printf("%d ", list->data);
        list = list->prev;
    }

    cout << endl;
}