#include "stack.h"
#include <stdio.h>
#include <string.h>

bool isRight(char* text)
{
    int size = strlen(text);
    for (int i = 0; i < size; i++)
    {
        switch (text[i])
        {
        case '(':
            push_stack(text[i]);
            break;
        case ')':
            if (stackIsEptpy() || pop_stack() != '(')
            {
                return false;
            }
            break;
        case '[':
            push_stack(text[i]);
            break;
        case ']':
            if (stackIsEptpy() || pop_stack() != '[')
            {
                return false;
            }
            break;
        case '{':
            push_stack(text[i]);
            break;
        case '}':
            if (stackIsEptpy() || pop_stack() != '{')
            {
                return false;
            }
            break;
        default:
            break;
        }
    }

    return stackIsEptpy();
}

int main()
{
    char* test1 = "(1te{st)}";    
    char* test2 = "(te[s]t)";
    printf("Test 2: %s - ", test2);

    if (isRight(test2))
    {
        printf("right!\n");
    }
    else
    {
        printf("incorrect!\n");
    }
}