#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

q_node* START = NULL;
q_node* END = NULL;

//-------------------- CHECK FUNCTION --------------------
bool is_empty()
{
    return START == NULL;
}

int count(q_node* list_copy)
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
void push_to_start(q_node** list, char* data)
{
    q_node* tmp = (q_node*)malloc(sizeof(q_node));
    //tmp->data = data;
    tmp->data = strdup(data);
    tmp->next = *list;
    *list = tmp;
}

void push_to_end(q_node* list_copy, char* data)
{
    if (START == NULL)
    {
        push_to_start(&START, data);
        END = START;
        return;
    }
    q_node* tmp = (q_node*)malloc(sizeof(q_node));
    tmp->data = strdup(data);
    tmp->next = NULL;
    list_copy->next = tmp;
    END = tmp;
}

//-------------------- POP FUNCTION --------------------
char* pop_from_start(q_node** list)
{
    if (*list == NULL)
    {
        printf("Element doesn't exist. List is empty.\n");
        return NULL;
    }
    q_node* tmp = *list;
    char* res = tmp->data;
    START = tmp->next;
    *list = tmp->next;
    free(tmp);
    return res;
}


void push_queue(char* data)
{
    push_to_end(END, data);
}

char* pop_queue()
{
    return pop_from_start(&START);
}
