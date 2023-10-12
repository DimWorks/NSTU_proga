/*

Python

def is_balanced(text, brackets="〈〉()[]{}"):
    opening, closing = brackets[::2], brackets[1::2]
    stack = [] # keep track of opening brackets types
    for character in text:
        if character in opening: # bracket
            stack.append(opening.index(character))
        elif character in closing: # bracket
            if stack and stack[-1] == closing.index(character):
                stack.pop()  # remove the matched pair
            else:
                return False # unbalanced (no corresponding opening bracket) or
                             # unmatched (different type) closing bracket
    return (not stack) # no unbalanced brackets*/

#include <stdio.h>
#include <string.h>

void isRight(char* text)
{
    sizet_t size = strlen(text);
    for(sizet_t i = 0; i < size; i++)
    {
        if(text[i] == '(')
        {
            push_stack(text[i]);
        }
        else if(text[i] == ')')
        {
            if(stackIsEptpy() || pop_stack() != '(')
            {
                return false;
            }
        }
    }

    return stackIsEptpy();
}

int main()
{

}