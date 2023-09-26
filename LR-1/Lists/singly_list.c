#include "singly_list.h"
#include <stdio.h>
#include <stdlib.h>

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

void* pop_from_tail(node* list_copy)
{
    if (list_copy == NULL)
    { 
        printf("Element doesn't exist. List is empty.\n"); 
        return NULL; 
    }
    node* tmp = list_copy;  
    while (list_copy->next != NULL)
    {
        tmp = list_copy; 
        list_copy = list_copy->next; 
    }
    void* res = list_copy->data; 
    tmp->next = NULL;  
    free(list_copy);
    return res;
}

//-------------------- PRINT FUNCTION --------------------
void print_from_head(node* list_copy)
{
    if (list_copy == NULL)
    { 
        printf("List is empty.\n");
        return; 
    }
    printf("Print from HEAD: ");
    while (list_copy != NULL)
    {
        printf("%d ", list_copy->data);
        list_copy = list_copy->next;   
    }
    printf("\n");
}

void real_print_from_tail(node* list_copy)
{
    if (list_copy != NULL)
    {
        real_print_from_tail(list_copy->next); 
        printf("%d ", list_copy->data); 
    }
}

void print_from_tail(node* list_copy)
{
    if (list_copy == NULL)
    { 
        printf("List is empty.\n"); 
        return;
    }
    printf("Print from TAIL: ");
    real_print_from_tail(list_copy);
    printf("\n");
}

//-------------------- EDIT FUNCTION --------------------
void edit_from_head(node* list_copy, void* data) 
{
    if (list_copy == NULL) 
    { 
        printf("Element to edit doesn't exist. List is empty.\n"); 
        return NULL; 
    }

    list_copy->data = data; 
}

void edit_from_tail(node* list_copy, void* data) 
{
    if (list_copy == NULL) 
    { 
        printf("Element to edit doesn't exist. List is empty.\n"); 
        return NULL; 
    }

    while (list_copy->next != NULL) 
    {
        list_copy = list_copy->next;
    }

    list_copy->data = data; 
}

void edit_from_position(node* list_copy, int position, void* data) 
{
    if (list_copy == NULL) 
    { 
        printf("Element to edit doesn't exist. List is empty.\n"); 
        return NULL; 
    }

    if (position < 1 || position > count(list_copy)) 
    { 
        printf("Impossible position for the element.\n"); 
        return NULL; 
    }

    for (int i = 1; i < position; i++, list_copy = (list_copy)->next);  //переход к запрашиваемому элементу
   
    list_copy->data = data; 
}