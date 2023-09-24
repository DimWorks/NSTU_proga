#pragma once



typedef struct trees
{
	int key;
	int data;
	struct node* right;
	struct node* left;
	struct node* parent;
	unsigned char level;
} node;

extern node* ROOT;

node* search_the_node(node* tree, int key);
void add_the_node(node* tree, int key, int data);
void create_node(int key, int data);
void showTree(node* tree, int p, int s);
node* finde_parend(node* parent, int key);
node* balance(node* p);