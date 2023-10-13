#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

node* HEAD;
node* TAIL;

//-------------------- PUSH FUNCTION --------------------
void push_to_head(node** list, char* data)
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data; 
    tmp->next = *list;
    *list = tmp;
    HEAD = tmp;
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
    *list = tmp->next;
    free(tmp);
    return res;
}

void push_stack(void* data)
{
	push_to_head(&HEAD, data);
}

char* pop_stack()
{
	//printf("%s\n", pop_from_head(&HEAD));
    return pop_from_head(&HEAD);
}

bool stackIsEptpy()
{
    if (HEAD == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}