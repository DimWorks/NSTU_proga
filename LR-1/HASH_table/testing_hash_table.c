#include "hash_table.h"
#include "../test.h"
#include <stdio.h>

#define CAPACITY 10 // Size of the Hash Table

void testing_hash_table() 
{
    HT* table = create_table(CAPACITY);
    
    ht_insert(table, "1", "First address");
    ht_insert(table, "2", "Second address");
    ht_insert(table, "12", "First address");

    print_search(table, "1");
    print_search(table, "2");
    print_search(table, "12");
    print_search(table, "3");

    ht_delete(table, "1");
    print_search(table, "1");
    ht_delete(table, "12");
    print_search(table, "12");

    
    print_table(table);

    free_table(table);
}
