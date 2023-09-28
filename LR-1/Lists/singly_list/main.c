#include "singly_list.h"
#include <stdio.h>
#include <stdlib.h>

int main() 
{
    node* list = NULL;  

    push_to_head(&list, "2"); 
    push_to_head(&list, "4"); 
    push_to_head(&list, "8"); 
    push_to_tail(list, "-1"); 
    push_to_tail(list, "0"); 
    print_from_head(list);  
    print_from_tail(list); 
        
    printf("Remove element from HEAD: %s\n", pop_from_head(&list)); 
    printf("Remove element from TAIL: %s\n", pop_from_tail(list)); 
    print_from_head(list); 
        
    print_from_head(list);

    return 0;
}
