#include <stdlib.h>
#include "stack.h"
#include "vector.h"

#define VEC_SIZE 1000

int stackIsEmpty(Stack * stack) {
    if( ((vector*)stack->top)->start_idx == -1 )
        return 1;
    return 0;
}

void push(Stack * stack, void * data) {
    if(stack->top == NULL) {
        stack->top = (void*)createVector(VEC_SIZE);
        stack->size = ((vector*)stack->top)->size;
    }

    add_to_end((vector*)stack->top, data);
}

void pop(Stack * stack) {
    if(stackIsEmpty(stack))
        return;
    delete_from_end((vector*)stack->top);
}

void * top (Stack * stack) {
    if(stackIsEmpty(stack))
        return NULL;
    return ((vector*)stack->top)->arr[((vector*)stack->top)->end_idx];
}

