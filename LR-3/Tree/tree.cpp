#include "tree.h"
#include <iostream>

#define RUS setlocale(LC_ALL, "RU");

node* tree::search_the_node(node* tree, int key)
{
	if (tree == NULL)
	{
		return NULL;
	}
	if (tree->key == key)
	{
		return tree;
	}
	else if (key < tree->key)
	{
		return search_the_node(tree->left, key);
	}
	else
	{
		return search_the_node(tree->right, key);
	}
}

node* tree::search_node(int key)
{
	return search_the_node(root, key);
}

node* tree::finde_parend(node* parent, int key)
{
	if (key < parent->key)
	{
		if (parent->left != NULL)
		{
			return finde_parend(parent->left, key);
		}
		else
		{
			return parent;
		}
	}
	else
	{
		if (parent->right != NULL)
		{
			return finde_parend(parent->right, key);
		}
		else
		{
			return parent;
		}
	}
}

node* tree::finde_the_parend(int key)
{
	return finde_parend(root, key);
}

void tree::create_node(int key, int data)
{
	node* tree = NULL;
	if ((tree = (node*)malloc(sizeof(node))))
	{
		tree->data = data;
		tree->key = key;
		tree->left = tree->right = NULL;
		if (root != NULL)
		{
			node* parent = finde_parend(root, key);

			tree->parent = parent;

			if (key < parent->key)
			{
				parent->left = tree;
			}
			else
			{
				parent->right = tree;
			}
		}
		else
		{
			tree->left = tree->right = tree->parent = NULL;
			root = tree;
		}
	}
	else
	{
		printf("Íåäîñòàòî÷íî ïàìÿòè. Íåâîçìîæíî ñîçäàòü óçåë.\n");
	}
}

node* get_max(node* tree)
{
	RUS

		if (tree == NULL)
		{
			printf("Äåðåâà íå ñóùåñòâóåò!\n");
			return NULL;
		}
	if (tree->right == NULL)
	{
		return tree;
	}
	return(get_max(tree->right));
}

node* get_min(node* tree)
{
	RUS

		if (tree == NULL)
		{
			printf("Äåðåâà íå ñóùåñòâóåò!\n");
			return NULL;
		}
	if (tree->left == NULL)
	{
		return tree;
	}
	return(get_max(tree->left));
}

void showLine(std::string c, int p, int s) {
	int t = s;
	for (int i = 0; i < p; i++)
	{
		printf(t & 1 ? "|  " : "   ");
		t /= 2;
	}
	std::cout << c;
}
void showTree(node* tree, int p, int s)
{
	if (tree == NULL)
	{
		return;
	}

	printf("%d", tree->data);
	printf("\n");

	if (tree->left != NULL) {
		showLine("|\n", p, s);
		showLine("L: ", p, s);
		showTree(tree->left, p + 1, s + ((tree->right == NULL ? 0 : 1) << p));
	}
	if (tree->right != NULL) {
		showLine("|\n", p, s);
		showLine("R: ", p, s);
		showTree(tree->right, p + 1, s);
	}
}

void tree::printTree()
{
	showTree(root, 0, 0);
}

void tree::delete_node(int key)
{
	node* tree = root;
	tree = search_the_node(root, key);
	if (tree == NULL)
	{
		return;
	}

	if (tree->left == NULL || tree->right == NULL)
	{
		if (tree->left == NULL)
		{
			node* tmp = tree->parent;
			if (key < tmp->key)
			{
				tmp->left = tree->right;
			}
			else
			{
				tmp->right = tree->right;
			}
			tmp = tree;
			tree = tree->right;
			if (tmp->right != NULL)
			{
				node* that_node = tmp->right;
				that_node->parent = tmp->parent;
			}
			if (tmp->left != NULL)
			{
				node* that_node = tmp->left;
				that_node->parent = tmp->parent;
			}
			free(tmp);
		}
		else
		{
			node* tmp = tree->parent;
			if (key < tmp->key)
			{
				tmp->left = tree->left;
			}
			else
			{
				tmp->right = tree->left;
			}
			tmp = tree;
			tree = tree->left;
			if (tmp->right != NULL)
			{
				node* that_node = tmp->right;
				that_node->parent = tmp->parent;
			}
			if (tmp->left != NULL)
			{
				node* that_node = tmp->left;
				that_node->parent = tmp->parent;
			}
			free(tmp);
		}
	}
	else if (tree->left == NULL && tree->right == NULL)
	{
		node* tmp = tree->parent;
		if (key < tmp->key)
		{
			tmp->left = NULL;
			free(tree);
		}
	}
	else
	{
		node* receiver = tree->right;
		if (receiver->left == NULL)
		{
			tree->data = receiver->data;
			tree->key = receiver->key;
			tree->right = receiver->right;
			tree->level = receiver->level;
			tree->parent = receiver->parent;
			return;
		}
		else
		{
			receiver = receiver->left;
			tree->data = receiver->data;
			tree->key = receiver->key;
			tree->right = receiver->parent;
			tree->level = receiver->level - 1;
			receiver = receiver->parent;
			receiver->left = NULL;
			return;
		}
	}
}

// Ãëóáèíà óçëà
int max_level_node(node* tree, int level)
{
	if (tree)
	{
		int new_level_1 = max_level_node(tree->left, level + 1);
		int new_level_2 = max_level_node(tree->right, level + 1);
		if (new_level_1 > level) level = new_level_1;
		if (new_level_2 > level) level = new_level_2;
	}
	return level;
}

// Ìàêñèìàëüíàÿ ãëóáèíà äåðåâà
int max_level(node* tree)
{
	return max_level_node(tree, -1);
}

void balance_tree(node** tree)
{
	if (*tree)
	{
		while (max_level((*tree)->left) - max_level((*tree)->right) >= 2)
		{
			node* tmp = (*tree)->left;
			(*tree)->left = tmp->right;
			tmp->right = *tree;
			*tree = tmp;
		}

		while (max_level((*tree)->right) - max_level((*tree)->left) >= 2)
		{
			node* tmp = (*tree)->right;
			(*tree)->right = tmp->left;
			tmp->left = *tree;
			*tree = tmp;
		}
		balance_tree(&((*tree)->left));
		balance_tree(&((*tree)->right));
	}
}

void tree::balance()
{
	if (root == NULL)
	{
		return;
	}
	balance_tree(&root);
	balance_tree(&root);
}

bool isFullBinaryTree(node* root)
{
	if (root == NULL)
	{
		return true;
	}

	// Checking the presence of children
	if (root->left == NULL && root->right == NULL)
	{
		return true;
	}

	if ((root->left) && (root->right))
	{
		return (isFullBinaryTree(root->left) && isFullBinaryTree(root->right));
	}

	return false;
}

bool tree::isFBT()
{
	return isFullBinaryTree(root);
}