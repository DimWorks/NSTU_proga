#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

s_node* S_HEAD;
s_node* S_TAIL;

//-------------------- PUSH FUNCTION --------------------
void push_to_head(s_node** list, char* data)
{
    s_node* tmp = (s_node*)malloc(sizeof(s_node));
    tmp->data = strdup(data);
    tmp->next = *list;
    *list = tmp;
}

//-------------------- POP FUNCTION --------------------
char* pop_from_head(s_node** list)
{
    if (*list == NULL)
    { 
        //printf("Element doesn't exist. List is empty.\n"); 
        //return NULL; 

        return "Element doesn't exist. List is empty.\n";
    }
    s_node* tmp = *list;
    char* res = strdup(tmp->data);
    *list = tmp->next;
    free(tmp);
    return res;
}

void push_stack(char* data)
{
	push_to_head(&S_HEAD, data);
}

char* pop_stack()
{
	return pop_from_head(&S_HEAD);
}
