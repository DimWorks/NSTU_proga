#pragma once

#include <stdbool.h>

typedef struct q_node
{
    char* data;
    struct q_node* next;
} q_node;

void push_queue(char*);
char* pop_queue();
bool is_empty();