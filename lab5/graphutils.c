#include <stdlib.h>
#include "graph.h"

void * createInt(int n) {
    int * p = malloc(sizeof(int));
    *p = n;

    return p;
}

int intcmp(void * p1, void * p2) {
    return *((int *)p1)-*((int *)p2);
}