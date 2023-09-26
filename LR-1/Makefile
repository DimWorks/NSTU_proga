link: main.o HASH_table/hash_table.o Lists/singly_list.o Queue/queue.o Stack/stack.o Tree/trees.o HASH_table/testing_hash_table.o Lists/testing_list.o Queue/testing_queue.o Stack/testing_stack.o Tree/testing_tree.o
	gcc main.o
main.o: main.c
	gcc -c main.c 
hash_table.o: HASH_table/hash_table.c
	gcc -c HASH_table/hash_table.c
list.o: Lists/singly_list.c
	gcc -c Lists/singly_list.c
queue.o: Queue/queue.c
	gcc -c Queue/queue.c
stack.o: Stack/stack.c
	gcc -c Stack/stack.c
trees.o: Tree/trees.c
	gcc -c Tree/trees.c
hash_table.o: HASH_table/testing_hash_table.c
	gcc -c HASH_table/testing_hash_table.c
list.o: Lists/testing_list.c
	gcc -c Lists/testing_singly_list.c
queue.o: Queue/testing_queue.c
	gcc -c Queue/testing_queue.c
stack.o: Stack/testing_stack.c
	gcc -c Stack/testing_stack.c
trees.o: Tree/testing_tree.c
	gcc -c Tree/testing_tree.c
