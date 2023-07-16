#include <stdlib.h>
#include "list.h"

ListNode * createListNode() {
    ListNode * ln = malloc(sizeof(ListNode));
    ln->data = NULL;
    ln->next = NULL;
    ln->prev = NULL;

    return ln;
}

void freeLn(ListNode * ln) {
    if(ln)
        free(ln);
}