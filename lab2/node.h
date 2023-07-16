#ifndef NODE_H
#define NODE_H

typedef struct Node {
    void * data;
    struct Node * next;
}Node;

void add_to_head(Node ** head, Node * node);

int delete_from_head(Node ** head);

Node * createNode(void * data);

#endif
