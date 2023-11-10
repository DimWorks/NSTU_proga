#include "trees.h"
//#include "../test.h"
#include <stdio.h>
#include <locale.h>



#define RUS setlocale(LC_ALL, "RU");

node* ROOT = NULL;

int main()
{
	RUS
	if (search_the_node(ROOT, 5) == NULL)
	{
		printf("\nЭлемент не найден!\n");
	}
	else
	{
		printf("\nНашёл!");
	}

	create_node(3, "3");
	
	create_node(15, "15");
	create_node(2, "2");
	create_node(1, "1");
	create_node(11, "11");
	create_node(7, "7");
	create_node(5, "5");
	create_node(6, "6");
	create_node(10, "10");
	create_node(14, "14");
	create_node(13, "13");
	create_node(4, "4");
	

	if (search_the_node(ROOT, 5) == NULL)
	{
		printf("\nЭлемент не найден!\n");
	}
	else
	{
		printf("\nНашёл!\n");
	}

	printTree(ROOT);

	if (!isFullBinaryTree(ROOT))
	{
		printf("The tree is a full binary tree\n");
	}
	else
	{
		printf("The tree is NOT a full binary tree\n");
	}

	balance();
	create_node(17, "17");
	create_node(16, "16");
	create_node(18, "18");

	printTree(ROOT);

	delete_node(14);
	delete_node(9);

	printTree(ROOT);

	delete_node(15);
	printTree(ROOT);

	return 0;
}