#ifndef STACK_H
#define STACK_H

typedef struct Stack {
    void * top;
    unsigned int size;
}Stack;

int stackIsEmpty(Stack * stack);

void push(Stack * stack, void * data);

void pop(Stack * stack);

void * top (Stack * stack);

#endif
