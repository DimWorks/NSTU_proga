#include "doubly_list.h"
#include <stdlib.h>
#include <stdio.h>

node* HEAD = NULL;
node* TAIL = NULL;

//-------------------- CHECK FUNCTION --------------------
int is_empty(node* list_copy) 
{
    return list_copy == NULL;
}

//-------------------- NUMBER OF NODES --------------------

int count(node* list_copy) {
    int i = 0;
    for (; list_copy != NULL; list_copy = list_copy->next)
    {
        i++;
    }
    return i;
}

//-------------------- PUSH FUNCTION --------------------

void push_to_head(node** list, void* data) 
{
    node* tmp = (node*)malloc(sizeof(node));
    tmp->data = data;
    tmp->next = *list;
    tmp->previous = NULL;
    if (*list != NULL)
    {
        tmp->next->previous = tmp;
    }
    else
    {
        TAIL = tmp;
    }
    *list = tmp;    
    HEAD = tmp;

}

void push_to_tail(node* list_copy, int data) 
{
    node* tmp = (node*)malloc(sizeof(node));    
    tmp->data = data;   
    tmp->next = NULL;  
    if (TAIL == NULL)
    {
        TAIL = tmp;
    }
    else
    {
        tmp->previous = TAIL;
        tmp->previous->next = tmp;
        TAIL = tmp;
    }
}

void push_to_position(node** list, int position, int data) 
{
    if (position < 1 || position > count(*list) + 1) 
    { 
        printf("Impossible position for the element\n"); 
        return; 
    } 
    if (position == 1) 
    { 
        push_to_head(list, data); 
        return; 
    }    
    if (position == count(*list) + 1) 
    {
        push_to_tail(*list, data);
        return; 
    }    
    node* tmp = (node*)malloc(sizeof(node));    
    node* list_copy = *list;   
    tmp->data = data; 
    for (int i = 1; i < position - 1; i++, list_copy = list_copy->next);    
    tmp->next = list_copy->next;    
    list_copy->next = tmp;  
}

//-------------------- POP FUNCTION --------------------
int pop_from_head(node** list) 
{
    if (*list == NULL) 
    {
        printf("Element to remove doesn't exist. List is empty.\n"); 
        return NULL; 
    }
    node* tmp = *list;  
    int res = tmp->data;   
    *list = tmp->next;  
    free(tmp);  
    return res;
}

int pop_from_tail(node* list_copy) 
{
    if (list_copy == NULL) 
    { 
        printf("Element to remove doesn't exist. List is empty.\n");
        return NULL; 
    }       

    list_copy = TAIL;
    node* tmp = list_copy->previous;   
    tmp->next = NULL;
    TAIL = tmp; 
    int res = list_copy->data;
    free(list_copy);  
    return res;
}

int pop_from_position(node** list, int position) 
{
    if (*list == NULL) 
    {
        printf("Element to remove doesn't exist. List is empty.\n"); 
        return NULL; 
    } 

    if (position < 1 || position > count(*list)) 
    { 
        printf("Impossible position for the element\n"); 
        return NULL; 
    }  
    if (position == 1) 
    {
        return pop_from_head(list); 
    } 
    if (position == count(*list)) 
    { 
        return pop_from_tail(*list); 
    } 
    node* list_copy = *list;    
    node* tmp = list_copy;  
    for (int i = 1; i < position; i++, list_copy = (list_copy)->next)
    {
        tmp = list_copy;
    }            
    int res = list_copy->data;  
    tmp->next = list_copy->next;    
    free(list_copy); 
    return res; 
}

//-------------------- EDIT FUNCTION --------------------
int edit_from_head(node* list_copy, int data) 
{
    if (list_copy == NULL)
    {
        printf("Element to edit doesn't exist. List is empty.\n"); 
        return NULL; 
    } 
    int res = list_copy->data; 
    list_copy->data = data; 
    return res;
}

int edit_from_tail(node* list_copy, int data) 
{
    if (list_copy == NULL) 
    {
        printf("Element to edit doesn't exist. List is empty.\n"); 
        return NULL;
    } 
    list_copy = TAIL;
    int res = list_copy->data;  
    list_copy->data = data; 
    return res;
}

int edit_from_position(node* list_copy, int position, int data) 
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
    for (int i = 1; i < position; i++, list_copy = (list_copy)->next);  
    int res = list_copy->data;  
    list_copy->data = data; 
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

void print_from_tail(node* list_copy) {
    if (list_copy == NULL) 
    { 
        printf("List is empty.\n"); 
        return; 
    }
    list_copy = TAIL;
    printf("Print from TAIL: ");
    while (list_copy != NULL)
    {
        printf("%d ", list_copy->data);
        list_copy = list_copy->previous;
    }
    
    printf("\n");
}

void print_element(node* list_copy, int position) {
    if (list_copy == NULL) 
    { 
        printf("List is empty.\n");
        return; 
    }
    if (position < 1 || position > count(list_copy)) 
    { 
        printf("Impossible position for the element.\n");
        return; 
    } 
    for (int i = 1; i < position; i++, list_copy = (list_copy)->next); 
    printf("Print %d element: %d", position, list_copy->data); 
    printf("\n");
}