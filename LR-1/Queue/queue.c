#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

node* HEAD = NULL;
node* TAIL = NULL;

//-------------------- CHECK FUNCTION --------------------
int is_empty(node* list_copy)
{
    return list_copy == NULL;   
}

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
void push_to_head(node** list, void* data)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data; 
    tmp->next = *list;
    *list = tmp;
    HEAD = tmp;
}

void push_to_tail(node* list_copy, void* data)
{
    if (list_copy == NULL)
    {
        push_to_head(&list_copy, data);
        TAIL = HEAD;
        return;
    }
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = NULL;
    while ((list_copy->next) != NULL)
    {
        list_copy = list_copy->next;
    }
    list_copy->next = tmp;
    TAIL = list_copy;
}

//-------------------- POP FUNCTION --------------------
void* pop_from_head(node** list)
{
    if (*list == NULL)
    { 
        printf("Element doesn't exist. List is empty.\n"); 
        return NULL; 
    }
    node* tmp = *list;
    void* res = tmp->data;
    *list = tmp->next;
    free(tmp);
    return res;
}


void push_queue(void* data)
{
	push_to_tail(TAIL, data);
}

void pop_queue()
{
	printf("%s\n", pop_from_head(&HEAD));
}