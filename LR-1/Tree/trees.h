#pragma once

#include <stdbool.h>

typedef struct node
{
	int key;
	void* data;
	struct node* right;
	struct node* left;
	struct node* parent;
	unsigned char level;
} node;

extern node* ROOT;

node* search_the_node(node* tree, int key);
void add_the_node(node* tree, int key, int data);
void create_node(int key, void* data);
void printTree(node* tree);
node* finde_parend(node* parent, int key);
void delete_node(int key);
void balance();