#include "doubly_list.h"
#include <stdio.h>
#include <stdlib.h>


//-------------------- MAIN --------------------
int main()
{
    node* list = NULL;

    push_to_head(&list, 2);
    push_to_head(&list, 4);
    push_to_head(&list, 8);
    push_to_head(&list, 9);
    push_to_tail(list, -1);
    push_to_tail(list, 0);
    print_from_head(list);
    print_from_tail(list);
    print_element(list, 2);

    push_to_position(&list, 5, 32);
    print_from_head(list);

    printf("Remove element from HEAD: %d\n", pop_from_head(&list));
    printf("Remove element from TAIL: %d\n", pop_from_tail(list));
    printf("Remove element from position: %d\n", pop_from_position(&list, 2));
    print_from_head(list);

    printf("Edit element was: %d\n", edit_from_head(list, 128));
    printf("Edit element was: %d\n", edit_from_tail(list, 1));
    printf("Edit element was: %d\n", edit_from_position(list, 2, 64));
    print_from_head(list);
    return 0;
}

