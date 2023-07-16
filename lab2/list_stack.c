#include <stdlib.h>
#include "stack.h"
#include "node.h"

int stackIsEmpty(Stack * stack) {
    Node * stack_top = (Node*)stack->top;
    if(stack_top)
        return 0;
    return 1;
}

void push(Stack * stack, void * data) {
    Node * tmp = createNode(data);
    Node ** stack_top = (Node**)&stack->top;
    add_to_head(stack_top, tmp);
    stack->size++;
}

void pop(Stack * stack) {
    Node ** stack_top = (Node**)&stack->top;
    stack->size -= delete_from_head(stack_top);
}

void * top (Stack * stack) {
    Node * stack_top = (Node*)stack->top;
    if(!stack_top)
        return NULL;
    return stack_top->data;
}
