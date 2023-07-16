#include <stdio.h>
#include <stdlib.h>
#include "node.h"

void add_to_head(Node ** head, Node * node) {
    if(!(*head)) {
        *head = node;
        return;
    }
    node->next = *head;
    *head = node;
}

int delete_from_head(Node ** head) {
    if(!(*head))
        return 0;
    Node * tmp = *head;
    *head = (*head)->next;
    free(tmp);
    return 1;
}

Node * createNode(void * data) {
    Node * tmp = (Node*)malloc(sizeof(Node));
    tmp->data = data;
    tmp->next = NULL;

    return tmp;
}
