#pragma once

class node
{
	friend class tree;
public:
	int key;
	int data;
	struct node* right;
	struct node* left;
	struct node* parent;
	unsigned char level;
};

class tree
{
	node* finde_parend(node* parent, int key);
	node* search_the_node(node* tree, int key);
public:
	node* root;
	tree() { root = nullptr; }
	node* search_node(int key);
	void add_the_node(int key, int data);
	void create_node(int key, int data);
	void printTree();
	node* finde_the_parend(int key);
	void delete_node(int key);
	void balance();
	bool isFBT();
};

