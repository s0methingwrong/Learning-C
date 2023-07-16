#ifndef QTREE_H
#define QTREE_H

#include <stdio.h>
#include "list.h"

typedef struct Qnode {
    struct Qnode * nw;
    struct Qnode * ne;
    struct Qnode * sw;
    struct Qnode * se;
    KeyType1 we_border;
    KeyType2 ns_border;
    List * leaf;
}Qnode;

typedef struct Qtree {
    Qnode * root;
    unsigned int size;
    unsigned int m_leaf_size;
}Qtree;


//interface

Qtree * createQtree(unsigned int m_leaf_size);

void freeQtree(Qtree * qtree);

void addToQtree(Qtree * qtree, KeyType1 k1, KeyType2 k2, InfoType info);

void delItemWithSeqNum(Qtree * qtree, KeyType1 k1, KeyType2 k2, int sn);

List * search(Qtree * qtree, KeyType1 k1, KeyType2 k2);

void traversalWithFile(Qtree * qtree, FILE * fp, void (*f)(FILE * fp, Qnode * qnode));

//utils

Qnode * createQnode();

void freeQnodeWithData(Qnode * qnode);

void splitQnode(Qnode * qnode);

void initInnerQnodes(Qnode * qnode);

int isLeaf(Qnode * qnode); //qnode must not to be NULL

int addToQnode(Qnode * qnode, Item * item, unsigned int m_leaf_size);

Qnode * getParentQnode(Qtree * qtree, Item * item);

Qnode * getLeafAndSetPrev(Qtree * qtree, Item * item, Qnode ** prev);

Qnode * getQnode(Qtree * qtree, Item * item);

int isEmptyLeafsChildren(Qnode * qnode); // qnode must not be NULL and children must be leafs

void delChildren(Qnode * qnode);

void traversalQnodeWithFile(Qnode * qnode, FILE * fp, void (*f)(FILE * fp, Qnode * qnode));

#endif