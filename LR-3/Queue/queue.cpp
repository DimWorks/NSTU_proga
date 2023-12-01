#include "queue.h"
#include <iostream>

using namespace std;

void queue::push_queue(int data)
{
    if (head == NULL)
    {
        node* tmp = (node*)malloc(sizeof(node));
        tmp->data = data;
        tmp->next = head;
        head = tmp;
        tail = head;
        return;
    }
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = NULL;
    node* list = head;
    while ((list->next) != NULL)
    {
        list = list->next;
    }
    list->next = tmp;
    tail = list;
}

int queue::pop_queue()
{
    if (head == NULL)
    {
        printf("Element doesn't exist. List is empty.\n");
        return NULL;
    }
    node* tmp = head;
    int res = tmp->data;
    head = tmp->next;
    free(tmp);
    return res;
}