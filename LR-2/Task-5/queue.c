#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

node* HEAD = NULL;
node* TAIL = NULL;

//-------------------- CHECK FUNCTION --------------------
bool is_empty()
{
    return HEAD == NULL;
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
void push_to_head(node** list, char* data)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data; 
    tmp->next = *list;
    *list = tmp;
    HEAD = tmp;
}

void push_to_tail(node* list_copy, char* data)
{
    if (HEAD == NULL)
    {
        push_to_head(&list_copy, data);
        TAIL = HEAD;
        return;
    }
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = NULL;

    //while ((list_copy->next) != NULL)
    //{
    //    list_copy = list_copy->next;
    //}
    list_copy->next = tmp;
    TAIL = tmp; // list_copy;
}

//-------------------- POP FUNCTION --------------------
char* pop_from_head(node** list)
{
    if (*list == NULL)
    { 
        printf("Element doesn't exist. List is empty.\n"); 
        return NULL; 
    }
    node* tmp = *list;
    char* res = tmp->data;
    HEAD = tmp->next;
    *list = tmp->next;
    free(tmp);
    return res;
}


void push_queue(char* data)
{
	push_to_tail(TAIL, data);
}

char* pop_queue()
{
    return pop_from_head(&HEAD);
}