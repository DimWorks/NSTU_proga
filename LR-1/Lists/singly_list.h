#pragma one

//-------------------- STRUCTURE --------------------
typedef struct node 
{ 
    void* data;  
    struct node* next; 
} node;

extern node* HEAD;
extern node* TAIL;

void push_to_head(node**, void*); 
void push_to_tail(node*, void*); 

void* pop_from_head(node**); 
void* pop_from_tail(node*); 

void print_from_head(node*); 
void print_from_tail(node*); 

int edit_from_head(node*, void*); 
int edit_from_tail(node*, void*);
int edit_from_position(node*, int, void*);